#include <stdio.h>
#include <string.h>
#include <err.h>
#include <blkid/blkid.h>


int main (int argc, char *argv[]) {

   system("lshw -С disk | grep diskname");
   system("lshw -C disk | grep product");
   system("lshw -C disk | grep size");

   system("lshw -C display | grep product");
   system("lshw -C display | grep vendor");
   system("lshw -C display | grep clock");
   system("lshw -C display | grep width");

   system("free");

   return 0;
}
