#include<stdio.h>
#include<unistd.h>

int main(){
    char s[202];
    int i;
    int pid = getpid();
    printf("PID%d\n",pid);
    sleep(10);
    printf("Done Sleeping\n");
    printf("What to execute in process?\n");
    scanf("%s", s);

    /*
      This is just a sample.
      You may need to use different version of the exec command in your coming assignment.
    */
    execlp(s, s, (char *)NULL);

    // The process would never reach this part if exec worked properly
    printf("This line will be printed iff there was an error in exec\n");
    return 0;
}
