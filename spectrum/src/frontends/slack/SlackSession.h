/**
 * Spectrum 2 Slack Frontend
 *
 * Copyright (C) 2015, Jan Kaluza <hanzz.k@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#pragma once

#include "transport/StorageBackend.h"
#include "rapidjson/document.h"

#include <string>
#include <algorithm>
#include <map>

#include "Swiften/Elements/Message.h"
#include "Swiften/Network/Timer.h"

#include <boost/signal.hpp>

namespace Transport {

class Component;
class StorageBackend;
class HTTPRequest;
class SlackRTM;
class SlackAPI;
class User;

class SlackSession {
	public:
		SlackSession(Component *component, StorageBackend *storageBackend, UserInfo uinfo);

		virtual ~SlackSession();

		boost::signal<void (const std::string &user)> onInstallationDone;

		void sendMessage(boost::shared_ptr<Swift::Message> message);

		void setPurpose(const std::string &purpose, const std::string &channel = "");

		void setUser(User *user) {
			m_user = user;
		}

	private:
		void handleRTMStarted();
		void handleMessageReceived(const std::string &channel, const std::string &user, const std::string &message, const std::string &ts, bool quiet);
		void handleImOpen(HTTPRequest *req, bool ok, rapidjson::Document &resp, const std::string &data);

		void handleJoinMessage(const std::string &message, std::vector<std::string> &args, bool quiet = false);
		void handleLeaveMessage(const std::string &message, std::vector<std::string> &args, bool quiet = false);
		void handleRegisterMessage(const std::string &message, std::vector<std::string> &args, bool quiet = false);

		void sendOnlineBuddies();

	private:
		Component *m_component;
		StorageBackend *m_storageBackend;
		UserInfo m_uinfo;
		std::string m_ownerName;
		SlackRTM *m_rtm;
		std::string m_ownerChannel;
		std::map<std::string, std::string> m_jid2channel;
		std::map<std::string, std::string> m_channel2jid;
		std::string m_slackChannel;
		User *m_user;
		Swift::Timer::ref m_onlineBuddiesTimer;
		std::map<std::string, std::string> m_onlineBuddies;
};

}
