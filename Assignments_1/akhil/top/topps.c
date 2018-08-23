/**
 * File              : topps.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 10.08.2018
 * Last Modified Date: 10.08.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */

#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <ctype.h>
#include <curses.h>
#include <errno.h>
#ifndef YIELDCPU_OFF
#include <sched.h>
#endif
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <values.h>
        /* need: 1 define + dev_to_tty */
#include "proc/devname.h"
        /* need: (ksym.c) open_psdb_message, wchan, close_psdb (redhat only) */
#include "proc/procps.h"
        /* need: 2 types + openproc, readproc, closeproc */
#include "proc/readproc.h"
        /* need: signal_name_to_number */
#include "proc/sig.h"
#ifdef USE_LIB_STA3
        /* need: status */
#include "proc/status.h"
#endif
        /* need: meminfo stuff */
#include "proc/sysinfo.h"
        /* need: procps_version + kernel version stuff */
#include "proc/version.h"
        /* need: sprint_uptime */
#include "proc/whattime.h"

#include "top.h"
static struct termios Savedtty,
                      Rawtty;
static int Ttychanged = 0;


static char *Myname;


static char RCfile [OURPATHSZ];

static int Page_size;


static int Cpu_tot,
            *Cpu_map;

static const char *States_fmts = STATES_line2x4;


static pid_t Monpids [MONPIDMAX] = { 0 };
static int Monpidsidx = 0;


static char Msg_delayed [SMLBUFSIZ];
static int Msg_awaiting = 0;
static int Screen_cols, Screen_rows, Max_lines;




static int Msg_row;


static int Mode_altscr;

static int Mode_irixps = 1;
static float Delay_time = DEF_DELAY;


static int No_ksyms = -1,
            PSDBopen = 0,
            Batch = 0,
            Loops = -1,
            Secure_mode = 0;



static char Cap_bold [CAPBUFSIZ] = "",
             Cap_clr_eol [CAPBUFSIZ] = "",
             Cap_clr_eos [CAPBUFSIZ] = "",
             Cap_clr_scr [CAPBUFSIZ] = "",
             Cap_curs_norm [CAPBUFSIZ] = "",
             Cap_curs_huge [CAPBUFSIZ] = "",
             Cap_home [CAPBUFSIZ] = "",
             Cap_norm [CAPBUFSIZ] = "",
             Cap_reverse [CAPBUFSIZ] = "",
             Caps_off [CAPBUFSIZ] = "";
static int Cap_can_goto = 0;
static WIN_t *Winstk [GROUPSMAX],
             *Curwin;



static int Frame_maxtask;

static float Frame_tscale;
static int Frame_srtflg,
              Frame_ctimes,
              Frame_cmdlin;
_SC_NUMx(P_PID, pid)
_SC_NUMx(P_PPD, ppid)
_SC_NUMx(P_PGD, pgrp)
_SC_NUMx(P_UID, euid)
_SC_STRx(P_USR, euser)
_SC_STRx(P_GRP, egroup)
_SC_NUMx(P_TTY, tty)
_SC_NUMx(P_PRI, priority)
_SC_NUMx(P_NCE, nice)
_SC_NUMx(P_CPN, processor)
_SC_NUM1(P_CPU, pcpu)

static int sort_P_TME (const proc_t **P, const proc_t **Q)
{
   if (Frame_ctimes) {
      if ( ((*P)->cutime + (*P)->cstime + (*P)->utime + (*P)->stime)
        < ((*Q)->cutime + (*Q)->cstime + (*Q)->utime + (*Q)->stime) )
           return SORT_lt;
      if ( ((*P)->cutime + (*P)->cstime + (*P)->utime + (*P)->stime)
        > ((*Q)->cutime + (*Q)->cstime + (*Q)->utime + (*Q)->stime) )
           return SORT_gt;
   } else {
      if ( ((*P)->utime + (*P)->stime) < ((*Q)->utime + (*Q)->stime))
         return SORT_lt;
      if ( ((*P)->utime + (*P)->stime) > ((*Q)->utime + (*Q)->stime))
         return SORT_gt;
   }
   return SORT_eq;
}

_SC_NUM1(P_VRT, size)
_SC_NUM2(P_SWP, size, resident)
_SC_NUM1(P_RES, resident)
_SC_NUM1(P_COD, trs)
_SC_NUM1(P_DAT, drs)
_SC_NUM1(P_SHR, share)
_SC_NUM1(P_FLT, maj_flt)
_SC_NUM1(P_DRT, dt)
_SC_NUMx(P_STA, state)

static int sort_P_CMD (const proc_t **P, const proc_t **Q)
{


   if (Frame_cmdlin && ((*P)->cmdline || (*Q)->cmdline)) {
      if (!(*Q)->cmdline) return Frame_srtflg * -1;
      if (!(*P)->cmdline) return Frame_srtflg;
      return Frame_srtflg *
         strncmp((*Q)->cmdline[0], (*P)->cmdline[0], (unsigned)Curwin->maxcmdln);
   }

   return Frame_srtflg * strcmp((*Q)->cmd, (*P)->cmd);
}

_SC_NUM1(P_WCH, wchan)
_SC_NUM1(P_FLG, flags)







static int chin (int ech, char *buf, unsigned cnt)
{
   int rc;

   fflush(stdout);
   if (!ech)
      rc = read(STDIN_FILENO, buf, cnt);
   else {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &Savedtty);
      rc = read(STDIN_FILENO, buf, cnt);
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &Rawtty);
   }

   tcflush(STDIN_FILENO, TCIFLUSH);
   return rc;
}





static const char *fmtmk (const char *fmts, ...)
{
   static char buf[BIGBUFSIZ];
   va_list va;

   va_start(va, fmts);
   vsnprintf(buf, sizeof(buf), fmts, va);
   va_end(va);
   return (const char *)buf;
}







static char *strim (int sp, char *str)
{
   static const char ws[] = "\b\f\n\r\t\v";
   char *p;

   if (sp)
      while ((p = strpbrk(str, ws))) *p = ' ';
   else
      if ((p = strpbrk(str, ws))) *p = 0;
   return str;
}






static const char *tg2 (int x, int y)
{
   return Cap_can_goto ? tgoto(cursor_address, x, y) : "";
}







static void bye_bye (int eno, const char *str)
{
   if (!Batch)
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &Savedtty);
   putp(tg2(0, Screen_rows));
   putp(Cap_curs_norm);
   putp("\n");
   if (str) {
      if (eno) perror(str);
      else {
         fputs(str, stderr);
         eno = 1;
      }
   }
   exit(eno);
}






static void stop (int dont_care_sig)
{
   (void)dont_care_sig;
   bye_bye(0, NULL);
}




static void std_err (const char *str)
{
   static char buf[SMLBUFSIZ];

   fflush(stdout);



   snprintf(buf, sizeof(buf), "\t%s: %s\n", Myname, str);
   if (!Ttychanged) {
      fprintf(stderr,"%s", buf);
      exit(1);
   }

   bye_bye(0, buf);
}






static void suspend (int dont_care_sig)
{
  (void)dont_care_sig;

   tcsetattr(STDIN_FILENO, TCSAFLUSH, &Savedtty);
   putp(tg2(0, Screen_rows));
   putp(Cap_curs_norm);
   fflush(stdout);
   raise(SIGSTOP);

   if (!Batch)
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &Rawtty);
}
static void capsmk (WIN_t *q)
{



   static int capsdone = 0;


   if (Batch) return;


   if (!capsdone) {
      strcpy(Cap_bold, enter_bold_mode ? enter_bold_mode : "");
      strcpy(Cap_clr_eol, clr_eol ? clr_eol : "");
      strcpy(Cap_clr_eos, clr_eos ? clr_eos : "");
      strcpy(Cap_clr_scr, clear_screen ? clear_screen : "");
      strcpy(Cap_curs_huge, cursor_visible ? cursor_visible : "");
      strcpy(Cap_curs_norm, cursor_normal ? cursor_normal : "");
      strcpy(Cap_home, cursor_home ? cursor_home : "");
      strcpy(Cap_norm, exit_attribute_mode ? exit_attribute_mode : "");
      strcpy(Cap_reverse, enter_reverse_mode ? enter_reverse_mode : "");
      snprintf(Caps_off, sizeof(Caps_off), "%s%s", Cap_norm, orig_pair ? orig_pair : "");
      if (tgoto(cursor_address, 1, 1)) Cap_can_goto = 1;
      capsdone = 1;
   }



   if (CHKw(q, Show_COLORS) && max_colors > 0) {
      strcpy(q->capclr_sum, tparm(set_a_foreground, q->summclr));
      snprintf(q->capclr_msg, sizeof(q->capclr_msg), "%s%s"
         , tparm(set_a_foreground, q->msgsclr), Cap_reverse);
      snprintf(q->capclr_pmt, sizeof(q->capclr_pmt), "%s%s"
         , tparm(set_a_foreground, q->msgsclr), Cap_bold);
      snprintf(q->capclr_hdr, sizeof(q->capclr_hdr), "%s%s"
         , tparm(set_a_foreground, q->headclr), Cap_reverse);
      snprintf(q->capclr_rownorm, sizeof(q->capclr_rownorm), "%s%s"
         , Caps_off, tparm(set_a_foreground, q->taskclr));
   } else {
      q->capclr_sum[0] = '\0';
      strcpy(q->capclr_msg, Cap_reverse);
      strcpy(q->capclr_pmt, Cap_bold);
      strcpy(q->capclr_hdr, Cap_reverse);
      strcpy(q->capclr_rownorm, Cap_norm);
   }

   snprintf(q->capclr_rowhigh, sizeof(q->capclr_rowhigh), "%s%s"
      , q->capclr_rownorm, CHKw(q, Show_HIBOLD) ? Cap_bold : Cap_reverse);
   q->len_rownorm = strlen(q->capclr_rownorm);
   q->len_rowhigh = strlen(q->capclr_rowhigh);


}
static void msg_save (const char *fmts, ...)
{
   char tmp[SMLBUFSIZ];
   va_list va;

   va_start(va, fmts);
   vsnprintf(tmp, sizeof(tmp), fmts, va);
   va_end(va);

   snprintf(Msg_delayed, sizeof(Msg_delayed), "\a***  %s  ***", strim(0, tmp));
   Msg_awaiting = 1;
}




static void show_msg (const char *str)
{
   PUTP("%s%s %s %s%s"
      , tg2(0, Msg_row)
      , Curwin->capclr_msg
      , str
      , Caps_off
      , Cap_clr_eol);
   fflush(stdout);
   sleep(MSG_SLEEP);
   Msg_awaiting = 0;
}




static void show_pmt (const char *str)
{
   PUTP("%s%s%s: %s%s"
      , tg2(0, Msg_row)
      , Curwin->capclr_pmt
      , str
      , Cap_curs_huge
      , Caps_off);
   fflush(stdout);
}
static void show_special (const char *glob)
{
   char tmp[BIGBUFSIZ], *cap, *lin_end, *sub_beg, *sub_end;
   int room;


   while ((lin_end = strchr(glob, '\n'))) {


      memcpy(tmp, glob, (unsigned)(lin_end - glob));

      tmp[lin_end - glob] = '\0';
      room = Screen_cols;
      sub_beg = sub_end = tmp;

      while (*sub_beg) {
         switch (*sub_end) {
            case 0:
               *(sub_end + 1) = '\0';
            case 1: case 2: case 3: case 4:
            case 5: case 6: case 7: case 8:
               cap = Curwin->captab[(int)*sub_end];
               *sub_end = '\0';
               PUTP("%s%.*s%s", cap, room, sub_beg, Caps_off);
               room -= (sub_end - sub_beg);
               sub_beg = ++sub_end;
               break;
            default:
               ++sub_end;
         }
         if (0 >= room) break;
      }

      putp(Cap_clr_eol);
      putp("\n");
      glob = ++lin_end;
   }




   if (*glob) PUTP("%.*s", Screen_cols, glob);
   fflush(stdout);
}






static char *ask4str (const char *prompt)
{
   static char buf[GETBUFSIZ];

   show_pmt(prompt);
   memset(buf, '\0', sizeof(buf));
   chin(1, buf, sizeof(buf) - 1);
   putp(Cap_curs_norm);
   return strim(0, buf);
}




static float get_float (const char *prompt)
{
   char *line;
   float f;

   if (!(*(line = ask4str(prompt)))) return -1;

   if (strcspn(line, ",.1234567890")) {
      show_msg("\aNot valid");
      return -1;
   }
   sscanf(line, "%f", &f);
   return f;
}




static int get_int (const char *prompt)
{
   char *line;
   int n;

   if (!(*(line = ask4str(prompt)))) return -1;

   if (strcspn(line, "-1234567890")) {
      show_msg("\aNot valid");
      return -1;
   }
   sscanf(line, "%d", &n);
   return n;
}
static const char *scale_num (unsigned num, const int width, const unsigned type)
{

   static float scale[] = { 1024, 1024*1024, 1024*1024*1024, 0 };




   static char nextup[] = { 'k', 'm', 'g', 0 };

   static char buf[TNYBUFSIZ];
   float *dp;
   char *up;


   if (width >= snprintf(buf, sizeof(buf), "%u", num)) return buf;


   for (up = nextup + type, dp = scale; *dp; ++dp, ++up) {

      if (width >= snprintf(buf, sizeof(buf), "%.1f%c", num / *dp, *up))
         return buf;

      if (width >= snprintf(buf, sizeof(buf), "%d%c", (int)(num / *dp), *up))
         return buf;
   }

   return "?";
}





static const char *scale_tics (TICS_t tics, const int width)
{
   static char buf[TNYBUFSIZ];
   unsigned ss;
   unsigned nt;
   unsigned ct;

   ct = ((tics * 100) / Hertz)%100 ;
   nt = tics / Hertz;
   if (width >= snprintf(buf, sizeof(buf), "%u:%02u.%02u", nt/60, nt%60, ct))
         return buf;
   ss = nt % 60;
   nt /= 60;
   if (width >= snprintf(buf, sizeof buf, "%u:%02u", nt, ss))
      return buf;
   nt /= 60;
   if (width >= snprintf(buf, sizeof buf, "%uh", nt))
      return buf;
   nt /= 24;
   if (width >= snprintf(buf, sizeof buf, "%ud", nt))
      return buf;
   nt /= 7;
   if (width >= snprintf(buf, sizeof buf, "%uw", nt))
      return buf;


   return "?";






}






static void time_elapsed (void)
{
    static struct timeval oldtimev;
    struct timeval timev;
    struct timezone timez;
    float et;

    gettimeofday(&timev, &timez);
    et = (timev.tv_sec - oldtimev.tv_sec)
       + (float)(timev.tv_usec - oldtimev.tv_usec) / 1000000.0;
    oldtimev.tv_sec = timev.tv_sec;
    oldtimev.tv_usec = timev.tv_usec;

    Frame_tscale = 100.0f / ((float)Hertz * (float)et * (Mode_irixps ? 1 : Cpu_tot));
}
static void *alloc_c (unsigned numb)
{
   void * p;

   if (!numb) ++numb;
   if (!(p = calloc(1, numb)))
      std_err("failed memory allocate");
   return p;
}


static void *alloc_r (void *q, unsigned numb)
{
   void *p;

   if (!numb) ++numb;
   if (!(p = realloc(q, numb)))
      std_err("failed memory allocate");
   return p;
}
static CPUS_t *refreshcpus (CPUS_t *cpus)
{
   static FILE *fp = NULL;
   int i;

   char buf[SMLBUFSIZ];



   if (!fp) {
      if (!(fp = fopen("/proc/stat", "r")))
         std_err(fmtmk("Failed /proc/stat open: %s", strerror(errno)));



      cpus = alloc_c((1 + Cpu_tot) * sizeof(CPUS_t));
   }
   rewind(fp);
   fflush(fp);


   if (!fgets(buf, sizeof(buf), fp)) std_err("failed /proc/stat read");
   if (4 > sscanf(buf, CPU_FMTS_JUST1
      , &cpus[Cpu_tot].u, &cpus[Cpu_tot].n, &cpus[Cpu_tot].s, &cpus[Cpu_tot].i, &cpus[Cpu_tot].w))
         std_err("failed /proc/stat read");

   if (1 == Cpu_tot) memcpy(cpus, &cpus[1], sizeof(CPUS_t));


   for (i = 0; 1 < Cpu_tot && i < Cpu_tot; i++) {



      if (!fgets(buf, sizeof(buf), fp)) std_err("failed /proc/stat read");
      if (4 > sscanf(buf, CPU_FMTS_MULTI
         , &cpus[i].u, &cpus[i].n, &cpus[i].s, &cpus[i].i, &cpus[i].w))
            std_err("failed /proc/stat read");
   }

   return cpus;
}






static proc_t **refreshprocs (proc_t **table, int flags)
{


   static unsigned savmax = 0;
   proc_t *ptsk = (proc_t *)-1;
   unsigned curmax = 0;
   PROCTAB* PT;

   if (Monpidsidx) {
      PT = openproc(flags | PROC_PID, Monpids);

      PT->procfs = NULL;
   } else
      PT = openproc(flags);


   while (curmax < savmax) {
      if (table[curmax]->cmdline) {
         free(*table[curmax]->cmdline);
         table[curmax]->cmdline = NULL;
      }
      if (!(ptsk = readproc(PT, table[curmax]))) break;
      ++curmax;
   }


   while (ptsk) {

      table = alloc_r(table, (curmax + 1) * sizeof(proc_t *));

      if ((ptsk = readproc(PT, NULL)))
         table[curmax++] = ptsk;
   }
   closeproc(PT);


   if (curmax >= savmax) {
      table = alloc_r(table, (curmax + 1) * sizeof(proc_t *));

      table[curmax] = alloc_c(sizeof(proc_t));
      savmax = curmax + 1;
   }

   table[curmax]->pid = -1;
   return table;



}







static void before (char *me)
{
   int i;


   Myname = strrchr(me, '/');
   if (Myname) ++Myname; else Myname = me;





   Cpu_tot = smp_num_cpus;

   Cpu_map = alloc_r(NULL, sizeof(int) * Cpu_tot);
   for (i = 0; i < Cpu_tot; i++)
      Cpu_map[i] = i;
   if(linux_version_code > LINUX_VERSION(2, 5, 41))
      States_fmts = STATES_line2x5;


   Page_size = getpagesize();
}
static void configs_read (void)
{
   static const char err_rc[] = "bad rcfile, you should delete '%s'";
   char fbuf[SMLBUFSIZ];
   FILE *fp;
   float delay = DEF_DELAY;
   char id;
   int i;

   snprintf(RCfile, sizeof(RCfile), ".%src", Myname);
   if (getenv("HOME"))
      snprintf(RCfile, sizeof(RCfile), "%s/.%src", getenv("HOME"), Myname);

   fp = fopen(SYS_RCFILE, "r");
   if (fp) {
      fbuf[0] = '\0';
      fgets(fbuf, sizeof(fbuf), fp);
      if (strchr(fbuf, 's')) Secure_mode = 1;

      fbuf[0] = '\0';
      fgets(fbuf, sizeof(fbuf), fp);
      fclose(fp);
      sscanf(fbuf, "%f", &delay);
   }
   fp = fopen(RCfile, "r");
   if (fp) {
      fgets(fbuf, sizeof(fbuf), fp);
      if (5 != (fscanf(fp, "Id:%c, "
         "Mode_altscr=%d, Mode_irixps=%d, Delay_time=%f, Curwin=%d\n"
         , &id, &Mode_altscr, &Mode_irixps, &delay, &i)) || RCF_FILEID != id)
            std_err(fmtmk(err_rc, RCfile));


      Curwin = Winstk[i];
      for (i = 0; i < GROUPSMAX; i++) {


         fscanf(fp, "%s\tfieldscur=%s\n"
            , Winstk[i]->winname, Winstk[i]->fieldscur);
         if (WINNAMSIZ <= strlen(Winstk[i]->winname)
         || strlen(DEF_FIELDS) != strlen(Winstk[i]->fieldscur))
            std_err(fmtmk(err_rc, RCfile));
         fscanf(fp, "\twinflags=%d, sortindx=%u, maxtasks=%d \n"
            , &Winstk[i]->winflags
            , &Winstk[i]->sortindx
            , &Winstk[i]->maxtasks);
         fscanf(fp, "\tsummclr=%d, msgsclr=%d, headclr=%d, taskclr=%d \n"
            , &Winstk[i]->summclr
            , &Winstk[i]->msgsclr
            , &Winstk[i]->headclr
            , &Winstk[i]->taskclr);
      }
      fclose(fp);
   }

   Secure_mode = getuid() ? Secure_mode : 0;
   if (!Secure_mode || !getuid()) Delay_time = delay;
}
static void parse_args (char **args)
{
   static const char usage[] =
      " -h?v | -bcisS -d delay -n iterations -p pid [,pid ...]";
   float tmp_delay = MAXFLOAT;
   char *p;

   while (*args) {
      char *cp = *(args++);

      while (*cp) {
         switch (*cp) {
            case '\0':
            case '-':
               break;
            case 'b':
               Batch = 1;
               break;
            case 'c':
               TOGw(Curwin, Show_CMDLIN);
               break;
            case 'd':
               if (cp[1]) ++cp;
               else if (*args) cp = *args++;
               else std_err("-d requires argument");

               if (1 != sscanf(cp, "%f", &tmp_delay))
                  std_err(fmtmk("bad delay '%s'", cp));
               break;
            case '?':
            case 'h': case 'H':
            case 'v': case 'V':
               std_err(fmtmk("%s\nusage:\t%s%s"
                  , procps_version, Myname, usage));
            case 'i':
               TOGw(Curwin, Show_IDLEPS);
               Curwin->maxtasks = 0;
               break;
            case 'n':
               if (cp[1]) cp++;
               else if (*args) cp = *args++;
               else std_err("-n requires argument");
               if (1 != sscanf(cp, "%d", &Loops) || 1 > Loops)
                  std_err(fmtmk("bad iterations arg '%s'", cp));
               break;
            case 'p':
               do {
                  if (cp[1]) cp++;
                  else if (*args) cp = *args++;
                  else std_err("-p argument missing");
                  if (Monpidsidx >= MONPIDMAX)
                     std_err(fmtmk("pid limit (%d) exceeded", MONPIDMAX));
                  if (1 != sscanf(cp, "%d", &Monpids[Monpidsidx])
                  || 0 > Monpids[Monpidsidx])
                     std_err(fmtmk("bad pid '%s'", cp));
                  if (!Monpids[Monpidsidx])
                     Monpids[Monpidsidx] = getpid();
                  Monpidsidx++;
                  if (!(p = strchr(cp, ',')))
                     break;
                  cp = p;
               } while (*cp);
               break;
            case 's':
               Secure_mode = 1;
               break;
            case 'S':
               TOGw(Curwin, Show_CTIMES);
               break;
            default :
               std_err(fmtmk("unknown argument '%c'\nusage:\t%s%s"
                  , *cp, Myname, usage));

         }


         if (*cp) cp += strspn(&cp[1], "- ,.1234567890") + 1;
      }
   }


   if (MAXFLOAT != tmp_delay) {
      if (Secure_mode || 0 > tmp_delay)
         msg_save("Delay time Not changed");
      else
         Delay_time = tmp_delay;
   }
}







int
process_command_line_arguments(int *argc, char **argv)
{
 char **av = argv;
 int count = *argc;
 float tmp_delay = MAXFLOAT;
 char *p;
 static const char usage[] =
      " -h?v | -bcisS -d delay -n iterations -p pid [,pid ...]";

 (*argc)--, av++;
 while((*argc > 0) && ('-' == *av[0])) {


  if('-' == *(av[0]+1)) {
   p = av[0];
   if((!strcmp(p + 2, "help")) || (!strcmp(p + 2, "version"))) {
      std_err(fmtmk("%s\nusage:\t%s%s"
      , procps_version, Myname, usage));
   }

    else {
               std_err(fmtmk("unknown argument '%s'\nusage:\t%s%s"
                  , p + 2, Myname, usage));
   }
  }


  while(*++av[0]) switch(*av[0]) {
   case 'b':
    Batch = 1;
    break;
   case 'c':
    TOGw(Curwin, Show_CMDLIN);
    break;
   case 'd':
    if(*(av[0]+1)) av[0]++;
    else if(av[1]) {
     av++; (*argc)--;
    } else
     std_err("-d requires argument");
    if(1 != sscanf(av[0], "%f", &tmp_delay))
     std_err(fmtmk("bad delay '%s'", av[0]));
    break;
   case '?':
   case 'h': case 'H':
   case 'v': case 'V':
      std_err(fmtmk("%s\nusage:\t%s%s"
      , procps_version, Myname, usage));
   case 'i':
    TOGw(Curwin, Show_IDLEPS);
    Curwin->maxtasks = 0;
    break;
   case 'n':
    if (*(av[0]+1)) av[0]++;
    else if (av[1]) {
     av++; (*argc)--;
    } else std_err("-n requires argument");
    if(1 != sscanf(av[0], "%d", &Loops) || 1 > Loops)
     std_err(fmtmk("bad iteration arg '%s'", av[0]));
    break;
   case 'p':
    do {
     if (*(av[0]+1)) av[0]++;
     else if (av[1]) {
      av++; (*argc)--;
     } else std_err("-p argument missing");
     if(Monpidsidx >= MONPIDMAX)
      std_err(fmtmk("pid limit (%d) exceeded", MONPIDMAX));
     if (1 != sscanf(av[0], "%d", &Monpids[Monpidsidx])
     || 0 > Monpids[Monpidsidx])
      std_err(fmtmk("bad pid '%s'", av[0]));
     if(!Monpids[Monpidsidx])
      Monpids[Monpidsidx] = getpid();
     Monpidsidx++;
     if(!(p = strchr(av[0], ',')))
      break;
     av[0] = p;
    } while (*av[0]);
    break;
   case 's':
    Secure_mode = 1;
    break;
   case 'S':
    TOGw(Curwin, Show_CTIMES);
    break;
   default:
               std_err(fmtmk("unknown argument '%c'\nusage:\t%s%s"
                  , *av[0], Myname, usage));
  }
  (*argc)--, av++;
 }

 if(MAXFLOAT != tmp_delay) {
  if(Secure_mode || 0 > tmp_delay)
   msg_save("Delay time Not changed");
  else
   Delay_time = tmp_delay;
 }

 return (count - *argc);
}




static void whack_terminal (void)
{
   struct termios newtty;





   setupterm(NULL, STDOUT_FILENO, NULL);


   if (!Batch) {
      if (-1 == tcgetattr(STDIN_FILENO, &Savedtty))
         std_err("failed tty get");
      newtty = Savedtty;
      newtty.c_lflag &= ~ICANON;
      newtty.c_lflag &= ~ECHO;
      newtty.c_cc[VMIN] = 1;
      newtty.c_cc[VTIME] = 0;

      Ttychanged = 1;
      if (-1 == tcsetattr(STDIN_FILENO, TCSAFLUSH, &newtty)) {
         putp(Cap_clr_scr);
         std_err(fmtmk("failed tty set: %s", strerror(errno)));
      }
      tcgetattr(STDIN_FILENO, &Rawtty);
      putp(Cap_clr_scr);
      fflush(stdout);
   }
}






static FTAB_t Fieldstab[] = {


   { "  PID ", "%5d ", -1, -1, _SF(P_PID), "Process Id" },
   { " PPID ", "%5d ", -1, -1, _SF(P_PPD), "Parent Process Pid" },
   { " PGID ", "%5d ", -1, -1, _SF(P_PGD), "Process Group Id" },
   { " UID ", "%4d ", -1, -1, _SF(P_UID), "User Id" },
   { "USER     ", "%-8.8s ", -1, -1, _SF(P_USR), "User Name" },
   { "GROUP    ", "%-8.8s ", -1, -1, _SF(P_GRP), "Group Name" },
   { "TTY      ", "%-8.8s ", 8, -1, _SF(P_TTY), "Controlling Tty" },
   { " PR ", "%3ld ", -1, -1, _SF(P_PRI), "Priority" },
   { " NI ", "%3ld ", -1, -1, _SF(P_NCE), "Nice value" },
   { "#C ", "%2d ", -1, -1, _SF(P_CPN), "Last used cpu (SMP)" },
   { "%CPU ", "%#4.1f ", -1, -1, _SF(P_CPU), "CPU usage" },
   { "  TIME ", "%6.6s ", 6, -1, _SF(P_TME), "CPU Time" },
   { "   TIME+  ", "%9.9s ", 9, -1, _SF(P_TME), "CPU Time, hundredths" },
   { "%MEM ", "%#4.1f ", -1, -1, _SF(P_RES), "Memory usage (RES)" },
   { " VIRT ", "%5.5s ", 5, SK_Kb, _SF(P_VRT), "Virtual Image (kb)" },
   { "SWAP ", "%4.4s ", 4, SK_Kb, _SF(P_SWP), "Swapped size (kb)" },
   { " RES ", "%4.4s ", 4, SK_Kb, _SF(P_RES), "Resident size (kb)" },
   { "CODE ", "%4.4s ", 4, SK_Kb, _SF(P_COD), "Code size (kb)" },
   { "DATA ", "%4.4s ", 4, SK_Kb, _SF(P_DAT), "Data+Stack size (kb)" },
   { " SHR ", "%4.4s ", 4, SK_Kb, _SF(P_SHR), "Shared Mem size (kb)" },
   { "nFLT ", "%4.4s ", 4, SK_no, _SF(P_FLT), "Page Fault count" },
   { "nDRT ", "%4.4s ", 4, SK_no, _SF(P_DRT), "Dirty Pages count" },



   { "S ", "%c ", -1, -1, _SF(P_STA), "Process Status" },



   { "Command ", "%-*.*s ", -1, -1, _SF(P_CMD), "Command line/name" },
   { "WCHAN     ", "%-9.9s ", -1, -1, _SF(P_WCH), "Sleeping in Function" },




   { "Flags    ", "%08lx ", -1, -1, _SF(P_FLG), "Task Flags <sched.h>" }

};
static void display_fields (const char *fields, const char *xtra)
{

   const char *p;
   int i, cmax = Screen_cols / 2, rmax = Screen_rows - 3;



   putp(Cap_bold);
   for (i = 0; i < MAXTBL(Fieldstab); ++i) {
      int b = (NULL != strchr(fields, i + 'A'));

      for (p = Fieldstab[i].head; ' ' == *p; ++p)
         ;
      PUTP("%s%s%c %c: %-10s = %s"
         , tg2((i / rmax) * cmax, (i % rmax) + 3)
         , b ? Cap_bold : Cap_norm
         , b ? '*' : ' '
         , b ? i + 'A' : i + 'a'
         , p
         , Fieldstab[i].desc);
   }
   if (xtra) {
      putp(Curwin->capclr_rownorm);
      while ((p = strchr(xtra, '\n'))) {
         ++i;
         PUTP("%s%.*s"
            , tg2((i / rmax) * cmax, (i % rmax) + 3)
            , (int)(p - xtra)
            , xtra);
         xtra = ++p;
      }
   }
   putp(Caps_off);


}




static void fields_reorder (void)
{
   static const char prompt[] =
      "Upper case letter moves field left, lower case right";
   char c, *p;
   int i;

   putp(Cap_clr_scr);
   putp(Cap_curs_huge);
   display_fields(Curwin->fieldscur, FIELDS_xtra);
   for (;;) {
      show_special(fmtmk(FIELDS_current
         , Cap_home, Curwin->fieldscur, Curwin->grpname, prompt));
      chin(0, &c, 1);
      i = toupper(c) - 'A';
      if (i < 0 || i >= MAXTBL(Fieldstab)) break;
      if (((p = strchr(Curwin->fieldscur, i + 'A')))
      || ((p = strchr(Curwin->fieldscur, i + 'a')))) {
         if (isupper(c)) p--;
         if (('\0' != p[1]) && (p >= Curwin->fieldscur)) {
            c = p[0];
            p[0] = p[1];
            p[1] = c;
         }
      }
   }
   putp(Cap_curs_norm);
}



static void fields_sort (void)
{
   static const char prompt[] =
      "Select sort field via field letter, type any other key to return";
   char phoney[PFLAGSSIZ];
   char c, *p;
   int i, x;

   strcpy(phoney, NUL_FIELDS);
   x = i = Curwin->sortindx;
   putp(Cap_clr_scr);
   putp(Cap_curs_huge);
   for (;;) {
      p = phoney + i;
      *p = toupper(*p);
      display_fields(phoney, SORT_xtra);
      show_special(fmtmk(SORT_fields
         , Cap_home, *p, Curwin->grpname, prompt));
      chin(0, &c, 1);
      i = toupper(c) - 'A';
      if (i < 0 || i >= MAXTBL(Fieldstab)) break;
      *p = tolower(*p);
      x = i;
   }
   if ((p = strchr(Curwin->fieldscur, x + 'a')))
      *p = x + 'A';
   Curwin->sortindx = x;
   putp(Cap_curs_norm);
}




static void fields_toggle (void)
{
   static const char prompt[] =
      "Toggle fields via field letter, type any other key to return";
   char c, *p;
   int i;

   putp(Cap_clr_scr);
   putp(Cap_curs_huge);
   for (;;) {
      display_fields(Curwin->fieldscur, FIELDS_xtra);
      show_special(fmtmk(FIELDS_current
         , Cap_home, Curwin->fieldscur, Curwin->grpname, prompt));
      chin(0, &c, 1);
      i = toupper(c) - 'A';
      if (i < 0 || i >= MAXTBL(Fieldstab)) break;
      if ((p = strchr(Curwin->fieldscur, i + 'A')))
         *p = i + 'a';
      else if ((p = strchr(Curwin->fieldscur, i + 'a')))
         *p = i + 'A';
   }
   putp(Cap_curs_norm);
}
static void win_colsheads (WIN_t *q)
{
   const char *h;
   int i, needpsdb = 0;


   for (i = 0, q->maxpflgs = 0; q->fieldscur[i]; i++) {
      if (isupper(q->fieldscur[i]))
         q->procflags[q->maxpflgs++] = q->fieldscur[i] - 'A';
   }



   if (Mode_altscr) strcpy(q->columnhdr, " "); else q->columnhdr[0] = '\0';
   for (i = 0; i < q->maxpflgs; i++) {
      h = Fieldstab[q->procflags[i]].head;

      if (Screen_cols < (int)(strlen(q->columnhdr) + strlen(h))) break;
      strcat(q->columnhdr, h);
   }




   q->maxpflgs = i;
   q->maxcmdln = Screen_cols
      - (strlen(q->columnhdr) - strlen(Fieldstab[P_CMD].head)) - 1;




   snprintf(q->columnhdr, sizeof(q->columnhdr), "%s"
      , Mode_altscr ? fmtmk("%d", q->winnum) : "");
   for (i = 0; i < q->maxpflgs; i++) {
      h = Fieldstab[q->procflags[i]].head;

      if (P_WCH == q->procflags[i]) needpsdb = 1;
      if (P_CMD == q->procflags[i])
         strcat(q->columnhdr
            , fmtmk(Fieldstab[P_CMD].fmts, q->maxcmdln, q->maxcmdln, h));
      else
         strcat(q->columnhdr, h);
   }


   if (needpsdb) {
      if (-1 == No_ksyms) {
         No_ksyms = 0;
         if (open_psdb_message(NULL, msg_save))


            No_ksyms = 1;
         else
            PSDBopen = 1;
      }
   }
}




static inline int win_fldviz (WIN_t *q, PFLG_t flg)
{
   PFLG_t *p = q->procflags + q->maxpflgs - 1;

   while (*p != flg && q->procflags < p) --p;
   return *p == flg;
}




static void win_names (WIN_t *q, const char *name)
{
   sprintf(q->winname, "%.*s", WINNAMSIZ -1, name);
   sprintf(q->grpname, "%d:%.*s", q->winnum, WINNAMSIZ -1, name);
}




static void win_select (char ch)
{
   static const char prompt[] = "Choose field group (1 - 4)";



   if (!ch) {
      show_pmt(prompt);
      chin(0, (char *)&ch, 1);
   }
   switch (ch) {
      case 'a':
         Curwin = Curwin->next;
         break;
      case 'w':
         Curwin = Curwin->prev;
         break;
      case '1': case '2':
      case '3': case '4':
         Curwin = Winstk[ch - '1'];
         break;
   }
}




static int win_warn (void)
{
   show_msg(fmtmk("\aCommand disabled, activate %s with '-' or '_'"
      , Curwin->grpname));


   return 0;
}





static void winsclr (WIN_t *q, int save)
{
   static int flgssav, summsav, msgssav, headsav, tasksav;

   if (save) {
      flgssav = q->winflags; summsav = q->summclr;
      msgssav = q->msgsclr; headsav = q->headclr; tasksav = q->taskclr;
      SETw(q, Show_COLORS);
   } else {
      q->winflags = flgssav; q->summclr = summsav;
      q->msgsclr = msgssav; q->headclr = headsav; q->taskclr = tasksav;
   }
   capsmk(q);
}




static void wins_colors (void)
{


   int clr = Curwin->taskclr, *pclr = &Curwin->taskclr;
   char ch, tgt = 'T';

   if (0 >= max_colors) {
      show_msg("\aNo colors to map!");
      return;
   }
   winsclr(Curwin, 1);
   putp(Cap_clr_scr);
   putp(Cap_curs_huge);

   do {
      putp(Cap_home);

      show_special(fmtmk(COLOR_help
         , procps_version, Curwin->grpname
         , CHKw(Curwin, Show_HIBOLD) ? "On" : "Off"
         , CHKw(Curwin, Show_COLORS) ? "On" : "Off"
         , tgt, clr, Curwin->winname));
      chin(0, &ch, 1);
      switch (ch) {
         case 'S':
            pclr = &Curwin->summclr;
            clr = *pclr;
            tgt = ch;
            break;
         case 'M':
            pclr = &Curwin->msgsclr;
            clr = *pclr;
            tgt = ch;
            break;
         case 'H':
            pclr = &Curwin->headclr;
            clr = *pclr;
            tgt = ch;
            break;
         case 'T':
            pclr = &Curwin->taskclr;
            clr = *pclr;
            tgt = ch;
            break;
         case '0': case '1': case '2': case '3':
         case '4': case '5': case '6': case '7':
            clr = ch - '0';
            *pclr = clr;
            break;
         case 'b':
            TOGw(Curwin, Show_HIBOLD);
            break;
         case 'z':
            TOGw(Curwin, Show_COLORS);
            break;
         case 'a':
         case 'w':
            win_select(ch);
            winsclr(Curwin, 1);
            clr = Curwin->taskclr, pclr = &Curwin->taskclr;
            tgt = 'T';
            break;
      }
      capsmk(Curwin);
   } while ('\n' != ch && 'q' != ch);

   if ('q' == ch)
      winsclr(Curwin, 0);
   putp(Cap_curs_norm);



}




static void wins_reflag (int what, int flg)
{
   WIN_t *w;

   w = Curwin;
   do {
      switch (what) {
         case Flags_TOG:
            TOGw(w, flg);
            break;
         case Flags_SET:
            SETw(w, flg);
            break;
         case Flags_OFF:
            OFFw(w, flg);
            break;
      }


      if (EQUWINS_cwo == flg) {
         w->maxtasks = 0;
         SETw(w, Show_IDLEPS | VISIBLE_tsk);
      }
      w = w->next;
   } while (w != Curwin);
}






static void wins_resize (int dont_care_sig)
{
   struct winsize wz;
   WIN_t *w;

   (void)dont_care_sig;
   Screen_cols = columns;
   Screen_rows = lines;
   if (-1 != (ioctl(STDOUT_FILENO, TIOCGWINSZ, &wz))) {
      Screen_cols = wz.ws_col;
      Screen_rows = wz.ws_row;
   }

   if (SCREENMAX < Screen_cols) Screen_cols = SCREENMAX;

   w = Curwin;
   do {
      win_colsheads(w);
      w = w->next;
   } while (w != Curwin);
}







static void windows_stage1 (void)
{
   static struct {
      const char *name;
      const char *flds;
      const int sort;
      const int clrs[4];
   } wtab[] = {
      { "Def", DEF_FIELDS, P_CPU,
         { COLOR_RED, COLOR_RED, COLOR_YELLOW, COLOR_RED } },
      { "Job", JOB_FIELDS, P_PID,
         { COLOR_CYAN, COLOR_CYAN, COLOR_WHITE, COLOR_CYAN } },
      { "Mem", MEM_FIELDS, P_MEM,
         { COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLUE, COLOR_MAGENTA } },
      { "Usr", USR_FIELDS, P_USR,
         { COLOR_YELLOW, COLOR_YELLOW, COLOR_GREEN, COLOR_YELLOW } },
   };
   WIN_t *w;
   char *pc;
   int i, x, *pi;


   w = alloc_c(sizeof(WIN_t) * GROUPSMAX);

   for (i = 0; i < GROUPSMAX; i++) {
      Winstk[i] = w;
      w->winnum = i + 1;
      strcpy(w->winname, wtab[i].name);
      strcpy(w->fieldscur, wtab[i].flds);
      w->sortindx = wtab[i].sort;
      w->winflags = DEF_WINFLGS;
      for (x = 0, pi = &w->summclr; x < 4; x++, pi++)
         *pi = wtab[i].clrs[x];
      w->captab[0] = Cap_norm;
      w->captab[1] = Cap_norm;
      w->captab[2] = Cap_bold;

      for (x = 3, pc = w->capclr_sum; x < CAPTABMAX; x++) {
         w->captab[x] = pc;
         pc += CLRBUFSIZ;
      }
      w->next = w + 1;
      w->prev = w - 1;
      ++w;
   }

   Winstk[3]->next = Winstk[0];
   Winstk[0]->prev = Winstk[3];
   Curwin = Winstk[0];
   Mode_altscr = 0;
}






static void windows_stage2 (void)
{
   int i;

   if (Batch) {
      Mode_altscr = 0;
      OFFw(Curwin, Show_COLORS | Show_HICOLS | Show_HIROWS);
   }
   wins_resize(0);
   for (i = 0; i < GROUPSMAX; i++) {
      win_names(Winstk[i], Winstk[i]->winname);
      capsmk(Winstk[i]);
   }
}
static void cpudo (CPUS_t *cpu, const char *pfx)
{



   STIC_t u_frme, s_frme, n_frme, i_frme, w_frme, tot_frme, tz;
   float scale;

   u_frme = ((tz = (STIC_t)cpu->u - cpu->u_sav) < 0 ? 0 : tz);
   s_frme = ((tz = (STIC_t)cpu->s - cpu->s_sav) < 0 ? 0 : tz);
   n_frme = ((tz = (STIC_t)cpu->n - cpu->n_sav) < 0 ? 0 : tz);
   i_frme = ((tz = (STIC_t)cpu->i - cpu->i_sav) < 0 ? 0 : tz);
   w_frme = ((tz = (STIC_t)cpu->w - cpu->w_sav) < 0 ? 0 : tz);
   tot_frme = u_frme + s_frme + n_frme + i_frme + w_frme;
   if (1 > tot_frme) tot_frme = 1;
   scale = 100.0 / (float)tot_frme;



   show_special(fmtmk(States_fmts
      , pfx
      , (float)u_frme * scale
      , (float)s_frme * scale
      , (float)n_frme * scale
      , (float)i_frme * scale
      , (float)w_frme * scale));
   Msg_row += 1;


   cpu->u_sav = cpu->u;
   cpu->s_sav = cpu->s;
   cpu->n_sav = cpu->n;
   cpu->i_sav = cpu->i;
   cpu->w_sav = cpu->w;


}







static void frame_states (proc_t **ppt, int show)
{
   static HIST_t *hist_sav;
   static HIST_t *hist_new;
   static unsigned hist_siz;
   unsigned total, running, sleeping, stopped, zombie;
   HIST_t *hist_tmp;


   hist_tmp = hist_sav;
   hist_sav = hist_new;
   hist_new = hist_tmp;

   total = running = sleeping = stopped = zombie = 0;
   time_elapsed();


   while (-1 != ppt[total]->pid) {
      TICS_t tics;
      proc_t *this = ppt[total];
      int i;

      switch (this->state) {
         case 'S':
         case 'D':
            sleeping++;
            break;
         case 'T':
            stopped++;
            break;
         case 'Z':
            zombie++;
            break;
         case 'R':
            running++;
            break;
      }
      if (total+1 >= hist_siz) {
         hist_siz = hist_siz * 5 / 4 + 100;
         hist_sav = alloc_r(hist_sav, sizeof(HIST_t) * hist_siz);
         hist_new = alloc_r(hist_new, sizeof(HIST_t) * hist_siz);
      }



      hist_new[total].pid = this->pid;
      hist_new[total].tics = tics = (this->utime + this->stime);


      for (i = 0; i < Frame_maxtask; i++) {
         if (this->pid == hist_sav[i].pid) {
            tics -= hist_sav[i].tics;
            break;
         }
      }


      this->pcpu = tics;

      total++;
   }


   Frame_maxtask = total;

   if (show) {
      static CPUS_t *smpcpu = NULL;


      show_special(fmtmk(STATES_line1
         , total, running, sleeping, stopped, zombie));
      Msg_row += 1;


      smpcpu = refreshcpus(smpcpu);

      if (CHKw(Curwin, View_CPUSUM)) {

         cpudo(&smpcpu[Cpu_tot], "Cpu(s):");
      } else {
         int i;
         char tmp[SMLBUFSIZ];

         for (i = 0; i < Cpu_tot; i++) {
            snprintf(tmp, sizeof(tmp), " Cpu%-2d:", Mode_irixps ? i : Cpu_map[i]);
            cpudo(&smpcpu[i], tmp);
         }
      }
   }
}




static void frame_storage (void)
{
   meminfo();
   if (CHKw(Curwin, View_MEMORY)) {
      show_special(fmtmk(MEMORY_line1
         , kb_main_total, kb_main_used, kb_main_free, kb_main_buffers));
      show_special(fmtmk(MEMORY_line2
         , kb_swap_total, kb_swap_used, kb_swap_free, kb_main_cached));
      Msg_row += 2;
   }
}





static void mkcol (WIN_t *q, PFLG_t idx, int sta, int *pad, char *buf, ...)
{
   char tmp[COLBUFSIZ];
   va_list va;

   va_start(va, buf);



   if (!CHKw(q, Show_HICOLS) || q->sortindx != idx) {
      vsprintf(buf, Fieldstab[idx].fmts, va);
   } else {
      vsnprintf(tmp, sizeof(tmp), Fieldstab[idx].fmts, va);
      sprintf(buf, "%s%s", q->capclr_rowhigh, tmp);
      *pad += q->len_rowhigh;
      if (!CHKw(q, Show_HIROWS) || 'R' != sta) {
         strcat(buf, q->capclr_rownorm);
         *pad += q->len_rownorm;
      }
   }
   va_end(va);
}




static void show_a_task (WIN_t *q, proc_t *task)
{







   char rbuf[ROWBUFSIZ];
   int j, x, pad;



   pad = Mode_altscr;
   if (pad) strcpy(rbuf, " "); else rbuf[0] = '\0';

   for (x = 0; x < q->maxpflgs; x++) {
      char cbuf[COLBUFSIZ];
      char a = task->state;
      PFLG_t i = q->procflags[x];
      unsigned s = Fieldstab[i].scale;
      unsigned w = Fieldstab[i].width;
      const char *f = Fieldstab[i].fmts;
      int b = (CHKw(q, Show_HICOLS) && q->sortindx == i);

      cbuf[0] = '\0';
      switch (i) {
         case P_CMD:
         { char *cmdptr, cmdnam[ROWBUFSIZ];

            if (!CHKw(q, Show_CMDLIN))
               cmdptr = task->cmd;
            else {
               cmdnam[0] = '\0';
               if (task->cmdline) {
                  j = 0;
                  do {



                     strcat(cmdnam
                        , fmtmk("%.*s ", q->maxcmdln, task->cmdline[j++]));



                     strim(1, cmdnam);
                     if (q->maxcmdln < (int)strlen(cmdnam)) break;
                  } while (task->cmdline[j]);
               } else {


                  strcpy(cmdnam, fmtmk(CMDLINE_FMTS, task->cmd));
               }
               cmdptr = cmdnam;
            }
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, q->maxcmdln, q->maxcmdln, cmdptr); else mkcol(q, i, a, &pad, cbuf, q->maxcmdln, q->maxcmdln, cmdptr); }while(0);
         }
            break;
         case P_COD:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num(PAGES_2K(task->trs), w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num(PAGES_2K(task->trs), w, s)); }while(0);
            break;
         case P_CPN:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->processor); else mkcol(q, i, a, &pad, cbuf, task->processor); }while(0);
            break;
         case P_CPU:
         { float u = (float)task->pcpu * Frame_tscale;

            if (99.9 < u) u = 99.9;
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, u); else mkcol(q, i, a, &pad, cbuf, u); }while(0);
         }
            break;
         case P_DAT:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num(PAGES_2K(task->drs), w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num(PAGES_2K(task->drs), w, s)); }while(0);
            break;
         case P_DRT:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num((unsigned)task->dt, w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num((unsigned)task->dt, w, s)); }while(0);
            break;
         case P_FLG:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, (long)task->flags); else mkcol(q, i, a, &pad, cbuf, (long)task->flags); }while(0);
            for (j = 0; cbuf[j]; j++)
               if ('0' == cbuf[j]) cbuf[j] = '.';
            break;
         case P_FLT:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num(task->maj_flt, w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num(task->maj_flt, w, s)); }while(0);
            break;
         case P_GRP:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->egroup); else mkcol(q, i, a, &pad, cbuf, task->egroup); }while(0);
            break;
         case P_MEM:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, (float)PAGES_2K(task->resident) * 100 / kb_main_total); else mkcol(q, i, a, &pad, cbuf, (float)PAGES_2K(task->resident) * 100 / kb_main_total); }while(0)
                                                                       ;
            break;
         case P_NCE:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, (long)task->nice); else mkcol(q, i, a, &pad, cbuf, (long)task->nice); }while(0);
            break;
         case P_PGD:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->pgrp); else mkcol(q, i, a, &pad, cbuf, task->pgrp); }while(0);
            break;
         case IP_PID:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->pid); else mkcol(q, i, a, &pad, cbuf, task->pid); }while(0);
            break;
         case P_PPD:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->ppid); else mkcol(q, i, a, &pad, cbuf, task->ppid); }while(0);
            break;
         case P_PRI:

            if (-99 > task->priority) task->priority = -99;
            else if (+99 < task->priority) task->priority = +99;
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, (long)task->priority); else mkcol(q, i, a, &pad, cbuf, (long)task->priority); }while(0);
            break;
         case P_RES:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num(PAGES_2K(task->resident), w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num(PAGES_2K(task->resident), w, s)); }while(0);
            break;
         case P_SHR:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num(PAGES_2K(task->share), w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num(PAGES_2K(task->share), w, s)); }while(0);
            break;
         case P_STA:



            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->state); else mkcol(q, i, a, &pad, cbuf, task->state); }while(0);

            break;
         case P_SWP:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num(PAGES_2K(task->size - task->resident), w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num(PAGES_2K(task->size - task->resident), w, s)); }while(0)
                                                                        ;
            break;
         case P_TME:
         case P_TM2:
         { TICS_t t;

            t = task->utime + task->stime;
            if (CHKw(q, Show_CTIMES))
               t += (task->cutime + task->cstime);
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_tics(t, w)); else mkcol(q, i, a, &pad, cbuf, scale_tics(t, w)); }while(0);
         }
            break;
         case P_TTY:
         { char tmp[TNYBUFSIZ];

            dev_to_tty(tmp, (int)w, task->tty, task->pid, ABBREV_DEV);
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, tmp); else mkcol(q, i, a, &pad, cbuf, tmp); }while(0);
         }
            break;
         case P_UID:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->euid); else mkcol(q, i, a, &pad, cbuf, task->euid); }while(0);
            break;
         case P_USR:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, task->euser); else mkcol(q, i, a, &pad, cbuf, task->euser); }while(0);
            break;
         case P_VRT:
            do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, scale_num(PAGES_2K(task->size), w, s)); else mkcol(q, i, a, &pad, cbuf, scale_num(PAGES_2K(task->size), w, s)); }while(0);
            break;
         case P_WCH:
            if (No_ksyms) {



               do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, fmtmk("x%08lx", (long)task->wchan)); else mkcol(q, i, a, &pad, cbuf, fmtmk("x%08lx", (long)task->wchan)); }while(0);

            } else {
               do{ if (!b) snprintf(cbuf, sizeof(cbuf), f, wchan(task->wchan)); else mkcol(q, i, a, &pad, cbuf, wchan(task->wchan)); }while(0);
            }
            break;

        }

        strcat(rbuf, cbuf);
   }


   PUTP("\n%s%.*s%s%s", (CHKw(q, Show_HIROWS) && 'R' == task->state)
      ? q->capclr_rowhigh : q->capclr_rownorm
      , Screen_cols + pad
      , rbuf
      , Caps_off
      , Cap_clr_eol);


}






static void do_key (unsigned c)
{

   static const char err_secure[] = "\aUnavailable in secure mode";





   switch (c) {
      case '1':






         TOGw(Curwin, View_CPUSUM);

         break;

      case 'a':
         if (Mode_altscr) Curwin = Curwin->next;
         break;

      case 'A':
         Mode_altscr = !Mode_altscr;
         wins_resize(0);
         break;

      case 'b':
         if (VIZCHKc) {
            if (!CHKw(Curwin, Show_HICOLS) && !CHKw(Curwin, Show_HIROWS))
               show_msg("\aNothing to highlight!");
            else {
               TOGw(Curwin, Show_HIBOLD);
               capsmk(Curwin);
            }
         }
         break;

      case 'c':
         VIZTOGc(Show_CMDLIN);
         break;

      case 'd':
      case 's':
         if (Secure_mode)
            show_msg(err_secure);
         else {
            float tmp =
               get_float(fmtmk("Change delay from %.1f to", Delay_time));
            if (tmp > -1) Delay_time = tmp;
         }
         break;

      case 'f':
         if (VIZCHKc) {
            fields_toggle();
            win_colsheads(Curwin);
         }
         break;

      case 'F':
      case 'O':
         if (VIZCHKc) {
            fields_sort();
            win_colsheads(Curwin);
         }
         break;

      case 'g':
         if (Mode_altscr) {
            char tmp[GETBUFSIZ];
            strcpy(tmp, ask4str(fmtmk("Rename window '%s' to (1-3 chars)"
               , Curwin->winname)));
            if (tmp[0]) win_names(Curwin, tmp);
         }
         break;

      case 'G':
         win_select(0);
         break;

      case 'h':
      case '?':
      { char ch;

         putp(Cap_clr_scr);
         putp(Cap_curs_huge);

         show_special(fmtmk(KEYS_help
            , procps_version
            , Curwin->grpname
            , CHKw(Curwin, Show_CTIMES) ? "On" : "Off"
            , Delay_time
            , Secure_mode ? "On" : "Off"
            , Secure_mode ? "" : KEYS_help_unsecured));
         chin(0, &ch, 1);
         if ('?' == ch || 'h' == ch) {
            do {
               putp(Cap_clr_scr);
               show_special(fmtmk(WINDOWS_help
                  , Curwin->grpname
                  , Winstk[0]->winname
                  , Winstk[1]->winname
                  , Winstk[2]->winname
                  , Winstk[3]->winname));
               chin(0, &ch, 1);
               win_select(ch);
            } while ('\n' != ch);
         }
         putp(Cap_curs_norm);
      }
         break;

      case 'i':
         VIZTOGc(Show_IDLEPS);
         break;

      case 'I':







         Mode_irixps = !Mode_irixps;
         show_msg(fmtmk("Irix mode %s", Mode_irixps ? "On" : "Off"));

         break;

      case 'k':
         if (Secure_mode) {
            show_msg(err_secure);
         } else {
            int sig, pid = get_int("PID to kill");

            if (-1 != pid) {
               sig = signal_name_to_number(
                  ask4str(fmtmk("Kill PID %d with signal [%i]"
                     , pid, DEF_SIGNAL)));
               if (-1 == sig) sig = DEF_SIGNAL;
               if (sig && kill(pid, sig))
                  show_msg(fmtmk("\aKill of PID '%d' with '%d' failed: %s"
                     , pid, sig, strerror(errno)));
            }
         }
         break;

      case 'l':
         TOGw(Curwin, View_LOADAV);
         break;

      case 'm':
         TOGw(Curwin, View_MEMORY);
         break;

      case 'n':
      case '#':
         if (VIZCHKc) {
            int num;
            if (-1 < (num = get_int(
               fmtmk("Maximum tasks = %d, change to (0 is unlimited)"
                  , Curwin->maxtasks))))
               Curwin->maxtasks = num;
         }
         break;

      case 'o':
         if (VIZCHKc) {
            fields_reorder();
            win_colsheads(Curwin);
         }
         break;

      case 'q':
         stop(0);

      case 'r':
         if (Secure_mode)
            show_msg(err_secure);
         else {
            int pid, val;

            pid = get_int("PID to renice");
            if (-1 == pid) break;
            val = get_int(fmtmk("Renice PID %d to value", pid));
            if (setpriority(PRIO_PROCESS, (unsigned)pid, val))
               show_msg(fmtmk("\aRenice of PID %d to %d failed: %s"
                  , pid, val, strerror(errno)));
         }
         break;

      case 'R':
         VIZTOGc(Qsrt_NORMAL);
         break;

      case 'S':
         if (VIZCHKc) {
            TOGw(Curwin, Show_CTIMES);
            show_msg(fmtmk("Cumulative time %s"
               , CHKw(Curwin, Show_CTIMES) ? "On" : "Off"));
         }
         break;

      case 't':
         TOGw(Curwin, View_STATES);
         break;

      case 'u':
         if (VIZCHKc)
            strcpy(Curwin->colusrnam, ask4str("Which user (blank for all)"));
         break;

      case 'w':
         if (Mode_altscr) Curwin = Curwin->prev;
         break;

      case 'W':
      { FILE *fp = fopen(RCfile, "w"); int i;

         if (fp) {
            fprintf(fp, "RCfile for \"%s with windows\"\t\t# shameless braggin'\n"
               , Myname);
            fprintf(fp, "Id:%c, "
               "Mode_altscr=%d, Mode_irixps=%d, Delay_time=%.3f, Curwin=%ld\n"
               , RCF_FILEID
               , Mode_altscr, Mode_irixps, Delay_time, Curwin - Winstk[0]);
            for (i = 0; i < GROUPSMAX; i++) {
               fprintf(fp, "%s\tfieldscur=%s\n"
                  , Winstk[i]->winname, Winstk[i]->fieldscur);
               fprintf(fp, "\twinflags=%d, sortindx=%d, maxtasks=%d\n"
                  , Winstk[i]->winflags
                  , Winstk[i]->sortindx
                  , Winstk[i]->maxtasks);
               fprintf(fp, "\tsummclr=%d, msgsclr=%d, headclr=%d, taskclr=%d\n"
                  , Winstk[i]->summclr
                  , Winstk[i]->msgsclr
                  , Winstk[i]->headclr
                  , Winstk[i]->taskclr);
            }
            fclose(fp);
            show_msg(fmtmk("Wrote configuration to '%s'", RCfile));
         } else
            show_msg(fmtmk("\aFailed '%s' open: %s", RCfile, strerror(errno)));
      }
         break;

      case 'x':
         if (VIZCHKc) {
            TOGw(Curwin, Show_HICOLS);
            capsmk(Curwin);
         }
         break;

      case 'y':
         if (VIZCHKc) {
            TOGw(Curwin, Show_HIROWS);
            capsmk(Curwin);
         }
         break;

      case 'z':
         if (VIZCHKc) {
            TOGw(Curwin, Show_COLORS);
            capsmk(Curwin);
         }
         break;

      case 'Z':
         wins_colors();
         break;

      case '-':
         if (Mode_altscr)
            TOGw(Curwin, VISIBLE_tsk);
         break;

      case '_':
         if (Mode_altscr)
            wins_reflag(Flags_TOG, VISIBLE_tsk);
         break;

      case '=':
         Curwin->maxtasks = 0;
         SETw(Curwin, Show_IDLEPS | VISIBLE_tsk);
         Monpidsidx = 0;
         break;

      case '+':
         if (Mode_altscr)
            SETw(Curwin, EQUWINS_cwo);
         break;

      case '<':
         if (VIZCHKc) {
            PFLG_t *p = Curwin->procflags + Curwin->maxpflgs - 1;
            while (*p != Curwin->sortindx)
               --p;
            if (--p >= Curwin->procflags)
               Curwin->sortindx = *p;
         }
         break;

      case '>':
         if (VIZCHKc) {
            PFLG_t *p = Curwin->procflags;
            while (*p != Curwin->sortindx)
               ++p;
            if (++p < Curwin->procflags + Curwin->maxpflgs)
               Curwin->sortindx = *p;
         }
         break;

      case '\n':
      case ' ':
         break;

      default:
         show_msg("\aUnknown command - try 'h' for help");
   }
}
static proc_t **do_summary (void)
{
   static proc_t **p_table = NULL;
   int p_flags = PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS;
   WIN_t *w;


   w = Curwin;
   do {
      if (!Mode_altscr || CHKw(w, VISIBLE_tsk)) {
         p_flags |= (CHKw(w, Show_CMDLIN) && win_fldviz(w, P_CMD)) ? PROC_FILLCOM : 0;
         p_flags |= win_fldviz(w, P_USR) ? PROC_FILLUSR : 0;
         p_flags |= win_fldviz(w, P_GRP) ? PROC_FILLGRP : 0;
      }
      if (Mode_altscr) w = w->next;
   } while (w != Curwin);

   if (!p_table) {

      p_table = refreshprocs(NULL, p_flags);
      frame_states(p_table, 0);
      putp(Cap_clr_scr);
      sleep(1);
   } else
      putp(Batch ? "\n\n" : Cap_home);




   if (CHKw(Curwin, View_LOADAV)) {
      if (!Mode_altscr)
         show_special(fmtmk(LOADAV_line, Myname, sprint_uptime()));
      else
         show_special(fmtmk(CHKw(Curwin, VISIBLE_tsk)
            ? LOADAV_line_alt
            : LOADAV_line
            , Curwin->grpname, sprint_uptime()));
      Msg_row += 1;
   }




   p_table = refreshprocs(p_table, p_flags);
   frame_states(p_table, CHKw(Curwin, View_STATES));



   frame_storage();
   sched_yield();

   SETw(Curwin, NEWFRAM_cwo);
   return p_table;



}





static void do_window (proc_t **ppt, WIN_t *q, int *lscr)
{






   int i, lwin;



   PUTP("\n%s%s%s%s", q->capclr_hdr, q->columnhdr, Caps_off, Cap_clr_eol);
      if (CHKw(q, Qsrt_NORMAL)) Frame_srtflg = 1;
         else Frame_srtflg = -1;
      Frame_ctimes = CHKw(q, Show_CTIMES);
      Frame_cmdlin = CHKw(q, Show_CMDLIN);
      qsort(ppt, (unsigned)Frame_maxtask, sizeof(proc_t *)
         , Fieldstab[q->sortindx].sort);




   if (!Batch) (*lscr)++;
   lwin = 1;
   i = 0;

   while ( -1 != ppt[i]->pid && *lscr < Max_lines
   && (!q->winlines || (lwin <= q->winlines)) ) {
      if ((CHKw(q, Show_IDLEPS)
      || ('S' != ppt[i]->state && 'Z' != ppt[i]->state))
      && ((!q->colusrnam[0])
      || (!strcmp(q->colusrnam, ppt[i]->euser)) ) ) {


         show_a_task(q, ppt[i]);
         if (!Batch) (*lscr)++;
         ++lwin;
      }
      ++i;
   }

   q->winlines = 0;
   OFFw(Curwin, FLGSOFF_cwo);




}






static void sohelpme (int wix, int max)
{
   int i, rsvd, size, wins;


   for (i = wix, rsvd = 0, wins = 0; i < GROUPSMAX; i++) {
      if (CHKw(Winstk[i], VISIBLE_tsk)) {
         rsvd += Winstk[i]->maxtasks;
         ++wins;
         if (max <= rsvd) break;
      }
   }
   if (!wins) wins = 1;

   size = (max - wins) - rsvd;
   if (0 <= size) size = max;
   size = (max - wins) / wins;




   for (i = wix ; i < GROUPSMAX; i++) {
      if (CHKw(Winstk[i], VISIBLE_tsk)) {
         Winstk[i]->winlines =
            Winstk[i]->maxtasks ? Winstk[i]->maxtasks : size;
      }
   }
}
static void so_lets_see_em (void)
{
   proc_t **ppt;
   int i, scrlins;

   Msg_row = scrlins = 0;
   ppt = do_summary();
   Max_lines = (Screen_rows - Msg_row) - 1;

   if (CHKw(Curwin, EQUWINS_cwo))
      wins_reflag(Flags_OFF, EQUWINS_cwo);


   putp(tg2(0, Msg_row));

   if (!Mode_altscr) {

      Curwin->winlines = Curwin->maxtasks;
      do_window(ppt, Curwin, &scrlins);
   } else {

      for (i = 0 ; i < GROUPSMAX; i++) {
         if (CHKw(Winstk[i], VISIBLE_tsk)) {
            sohelpme(i, Max_lines - scrlins);
            do_window(ppt, Winstk[i], &scrlins);
         }
         if (Max_lines <= scrlins) break;
      }
   }



   PUTP("%s%s%s", Cap_clr_eos, tg2(0, Msg_row), Cap_clr_eol);
   fflush(stdout);
}
int main (int dont_care_argc, char **argv)
{

   before(*argv);
   windows_stage1();
   configs_read();

   process_command_line_arguments(&dont_care_argc, argv);
   whack_terminal();
   windows_stage2();

   signal(SIGALRM, stop);
   signal(SIGHUP, stop);
   signal(SIGINT, stop);
   signal(SIGPIPE, stop);
   signal(SIGQUIT, stop);
   signal(SIGTERM, stop);
   signal(SIGTSTP, suspend);
   signal(SIGTTIN, suspend);
   signal(SIGTTOU, suspend);
   signal(SIGCONT, wins_resize);
   signal(SIGWINCH, wins_resize);

   for (;;) {
      struct timeval tv;
      fd_set fs;
      char c;

      so_lets_see_em();

      if (Msg_awaiting) show_msg(Msg_delayed);
      if (0 < Loops) --Loops;
      if (!Loops) stop(0);

      if (Batch)
         sleep((unsigned)Delay_time);
      else {
         tv.tv_sec = Delay_time;
         tv.tv_usec = (Delay_time - (int)Delay_time) * 1000000;
         FD_ZERO(&fs);
         FD_SET(STDIN_FILENO, &fs);
         if (0 < select(STDIN_FILENO+1, &fs, NULL, NULL, &tv)
         && 0 < chin(0, &c, 1))
            do_key((unsigned)c);
      }
   }
   return 0;
}
