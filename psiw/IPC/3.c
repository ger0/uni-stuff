#define MAX 512
main(int argc, char*argv[]) {
    execvp("ls", argv);
    exit(0);
}
