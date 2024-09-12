char helpMessage[] = "Sentinel [OPTIONS]:\n\n[OPTIONS]:\n-s: To start service\n--help: To show help message";
int input, output, dmesg, sysLog, gpuLog;
long inputSize;
char dmesgOutput[106] = "";
char gpuFileOutput[116] = "";
char syslogOutput[109] = "";
char _date[100];
