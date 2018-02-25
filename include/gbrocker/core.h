#ifndef GBROCKER_CORE_H
#define GBROCKER_CORE_H

namespace gbrocker {
	using id_t = uint16_t;

	class theme;
	class notifier;

	class theme {
	public:
		std::list<notifier*> notifiers; 
		std::string str;
		id_t id;
		void resend(char* data, size_t size);
		theme(const std::string& str, id_t id) : str(str), id(id) {}
	};

	class notifier {
		std::list<theme*> themes;
	};

	std::unordered_map<std::string, theme*> themes_strmap;
	std::unordered_map<id_t, theme*> themes_idmap;

	void create_theme(const std::string& str, id_t id) {
		theme* thm = new theme(str, id);
		themes_strmap.emplace(str, thm);
		themes_idmap.emplace(id, thm);
	}

	void delete_theme(theme* thm) {
		themes_strmap.erase(thm->str);
		themes_idmap.erase(thm->id);
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

	void delete_theme(id_t id) {
		auto it = themes_idmap.find(id);
		if (it == themes_idmap.end()) {
			return;
		}
		theme* thm = it->second;
		delete_theme(thm);
	}
}

#endif