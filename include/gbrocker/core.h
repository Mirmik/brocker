#ifndef GBROCKER_CORE_H
#define GBROCKER_CORE_H

#include <list>
#include <unordered_map>

namespace gbrocker {
	using id_t = uint16_t;

	class theme;
	class notifier;

	class theme {
	public:
		std::list<notifier*> notifiers; 
		std::string str;
		void resend(char* data, size_t size);
		theme(const std::string& str, id_t id) : str(str) {}
	};

	class notifier {
		std::list<theme*> themes;
	};
	std::unordered_map<std::string, theme*> themes_strmap;

	void create_theme(const std::string& str, id_t id) {
		theme* thm = new theme(str, id);
		themes_strmap.emplace(str, thm);
	}

	void delete_theme(theme* thm) {
		themes_strmap.erase(thm->str);
		delete thm;
	}		

	void delete_theme(const std::string& str) {
		auto it = themes_strmap.find(str);
		if (it == themes_strmap.end()) {
			return;
		}
		theme* thm = it->second;
		delete_theme(thm);
	}

}

#endif