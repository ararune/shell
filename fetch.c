#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <libgen.h>
#include <sys/sysinfo.h>
#include "fetch.h"

#define COLOR_CYAN "\033[1;36m"
#define COLOR_WHITE "\033[1;37m"
#define COLOR_RESET "\033[0m"
#define LINE "__________________________________________________"

void print_property(const char *name, const char *value) {
   printf(COLOR_CYAN"%-15s"COLOR_RESET"%s\n", name, value);
}

void get_os_info() {
   struct utsname uname_data;
   if (uname(&uname_data) == -1) {
      perror("lsh");
      return;
   }
   print_property("OS", uname_data.sysname);
   print_property("Kernel", uname_data.release);
   print_property("DE", getenv("DESKTOP_SESSION") ?: "");
}

void get_shell_info() {
   char *shell_path = getenv("SHELL");
   char *shell_name = "";
   if (shell_path) {
      shell_name = basename(shell_path);
   }
   print_property("Shell", shell_name);
}



void get_gpu_info() {
   print_property("GPU", "TODO"); // TODO: Implement GPU detection
}

void get_cpu_info() {
   FILE *fp = fopen("/proc/cpuinfo", "r");
   if (fp) {
      char line[256];
      while (fgets(line, sizeof(line), fp)) {
         if (strstr(line, "model name")) {
            char *colon = strchr(line, ':');
            if (colon) {
               printf(COLOR_CYAN"%-15s"COLOR_RESET"%s", "CPU", colon+2); // skip colon and space
               break;
            }
         }
      }
      fclose(fp);
   } else {
      print_property("CPU", "Unknown");
   }
}

void get_ram_info() {
   struct sysinfo info;
   if (sysinfo(&info) != 0) {
      perror("lsh");
      return;
   }
   double total_mem_gb = (double) info.totalram / (1024 * 1024 * 1024);
   double used_mem_gb = (double) (info.totalram - info.freeram) / (1024 * 1024 * 1024);
   char ram_info[100];
   snprintf(ram_info, sizeof(ram_info), "%.2f GB / %.2f GB", used_mem_gb, total_mem_gb);
   printf(COLOR_CYAN"%-15s"COLOR_RESET"%s\n", "Memory", ram_info);
}
int lsh_fetch(char **args) {
   get_os_info();
   get_shell_info();
   get_cpu_info();
   get_gpu_info();
   get_ram_info();
   return 1;
}

