# miner_monitor
Monitor the temperature and connection status of your miner software

Before using this program you will need to install daemon first.

Installing daemon package on Ubuntu 16.04 (Xenial Xerus):
```shell
  sudo apt-get update
  sudo apt-get install daemon
```

Once daemon has been installed you will have to create a symbolic link to your mining script file (the file you execute which has all of your settings configured).
```shell    
    sudo ln -s $(PWD)/my_script.sh  /usr/bin/my_command
```

When you are all set, all you have to do is edit the constants in the main.c file and compile.

```C
#define COMMAND  "daemon your_edit"
#define PIDOF 	 "pidof your_edit"
```

You can also set other values as well
```C
  #define MAXTEMP      81    /*  Temperature limit, when reached the program goes in the recovery state. */
  #define RCV_INTERVAL 10   /* How many minutes should the program be in the recovery state. */
  #define MON_INRERVAL  5    /* Every how many minutes should the program monitor your miner. */
 ```
 
 The log file is placed in your home directory, you can change that by editing:
 ```C
 snprintf(path, sizeof(path),"/home/%s/gpu_temp.md",pwd->pw_name);    /* log file path: /home/$USER/gpu_temp.md */
 ```
