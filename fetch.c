#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <libgen.h>
#include <sys/sysinfo.h>
#include "fetch.h"

#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MINUTE 60

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
   FILE *fp = fopen("/etc/os-release", "r");
   if (fp) {
      char line[256];
      while (fgets(line, sizeof(line), fp)) {
         if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
            printf(COLOR_CYAN"%-15s"COLOR_RESET"%.*s\n", "OS", (int)strlen(line)-15, line+13);
            break;
         }
      }
      fclose(fp);
   }
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
   FILE *fp = popen("lspci | grep -i vga", "r");
   if (fp) {
      char line[256];
      if (fgets(line, sizeof(line), fp)) {
         char *colon = strchr(line, ':');
         if (colon) {
            printf(COLOR_CYAN"%-15s"COLOR_RESET"%s", "GPU", colon+2); // skip colon and space
         }
      }
      pclose(fp);
   } else {
      print_property("GPU", "Unknown");
   }
}
void get_uptime_info() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("lsh");
        return;
    }

    long seconds = info.uptime;
    int days = seconds / SECONDS_PER_DAY;
    int hours = (seconds % SECONDS_PER_DAY) / SECONDS_PER_HOUR;
    int minutes = (seconds % SECONDS_PER_HOUR) / SECONDS_PER_MINUTE;

    printf(COLOR_CYAN"%-15s"COLOR_RESET, "Uptime");
    if (days > 0) {
        printf("%d day%s, ", days, (days > 1 ? "s" : ""));
    }

    if (hours > 0) {
        printf("%d hr%s, ", hours, (hours > 1 ? "s" : ""));
    }

    printf("%d min%s\n", minutes, (minutes > 1 ? "s" : ""));
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
   get_uptime_info();
   get_cpu_info();
   get_gpu_info();
   get_ram_info();

   return 1;
}

