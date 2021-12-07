#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int *foo=NULL;
void sighandler(int x) {
*foo=20;
}
int main() {
// volatile int bar=10;
int bar=30;
int baz=15;
foo=&baz;
foo++; // foo is pointing to bar now, hopefully...
signal(SIGINT, sighandler);
sleep(2);
printf("%d\n", bar);
}