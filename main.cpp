#include <gxx/getopt/cliopts.h>
#include <gxx/print.h> 

#include <gbrocker/core.h>
#include <g0/service.h>
#include <g0/gate/udp.h>

#include <gxx/log/logger.h>
#include <gxx/log/targets/stdout.h>

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

gxx::log::stdout_target constgt;
gxx::log::logger syslog("syslog");

void udp_gate_callback_handler(int sig) {
	syslog.trace("udp_gate_callback_handler");
}

int main(int argc, char* argv[]) {

	//Инициализация системного лога.
	syslog.set_pattern("[{logger}, {level}, {time}] {msg}");
	syslog.link(constgt);
	syslog.info("syslog inited");

	//Разбор опций командной строки.
	gxx::cliopts opts;
	opts.add_integer("port", 'p', 13975);
	opts.add_bool("debug", 'd', false);
	opts.parse(1, argc, argv);

	//Выбор уровня логирования.
	bool debug_mode = opts.get_bool("debug");
	if (debug_mode) syslog.set_level(gxx::log::level::trace);
	else 			syslog.set_level(gxx::log::level::info);
	syslog.debug("debug mode");

	//Инициализация UDP шлюза системы g0.
	int uport = opts.get_integer("port");
	syslog.debug("udpgate port: {}", uport);
	g0::udp_gate ugate(uport);

	//Перевод UDP шлюза в сигнальный режим.
	int ufd = ugate.get_fd();
	fcntl(ufd, F_SETOWN, getpid());
	fcntl(ufd, F_SETSIG, SIGUSR1);
	fcntl(ufd,F_SETFL,fcntl(ufd,F_GETFL) | O_NONBLOCK | O_ASYNC); 
   	signal(SIGUSR1, udp_gate_callback_handler);

   	while(1);
}