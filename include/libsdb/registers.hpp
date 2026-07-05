#ifndef SDB_REGISTERS_HPP
#define SDB_REGISTERS_HPP

#include <sys/user.h>
#include <libsdb/register_info.hpp>

namespace sdb {
	class process;
	class registers {
	public:
		registers() = delete;
		registers(const registers&) = delete;
		registers& operator=(const registers&) = delete;

		using value = /*?*/;
		value read(const register_info& info) const;
		void write(const register_info& info, value val) const;

	private:
		friend process;
		registers(process& proc) : proc_(&proc) {}

		user data_;
		process* proc_;
	};
}

#endif
