#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char* fichier_log;
#include "tools.h"
#include "ModuleTestServer/test_server.h"
#include "ModuleCopyList/copy_list.h"
#include "ModuleSynchroList/synchro_list.h"
