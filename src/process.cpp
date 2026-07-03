#include <libsdb/process.hpp>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

std::unique_ptr<sdb::process> sdb::process::launch(
	std::filesystem::path path) {
	pid_t pid;
	if ((pid = fork()) < 0) {
		// Error: fork failed
	}

	if (pid == 0) {
		if (ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) < 0) {
			// Error: tracing failed
		}
		if (execlp(path.c_str(), path.c_str(), nullptr) < 0) {
			// Error: exec failed
		}
	}

	std::unique_ptr<process> proc (new process(pid, /*terminate_on_end_=*/true));
	proc->wait_on_signal();

	return proc;
}

std::unique_ptr<sdb::process> sdb::process::attach(
	pid_t pid) {
	if (pid == 0) {
		// Error: Invalid PID
	}
	if (ptrace(PTRACE_ATTACH, pid, nullptr, nullptr) < 0) {
		// Error: Could not attach
	}

	std::unique_ptr<process> proc (new process(pid, /*terminate_on_end_=*/false));
	proc->wait_on_signal();

	return proc;
}
