/*
 * CPW Woodpecker Server
 * Copyright (C) 2021 CPW Online support@cpwonline.org
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Factory/business_handler.h"

using namespace CPW::Factory;

BusinessHandler::~BusinessHandler()
{

}

void BusinessHandler::HandleGETMethod_(HTTPServerRequest& request, HTTPServerResponse& response)
{
	get_current_query_actions()->IdentifyFilters_();
	get_current_query_actions()->ComposeQuery_(TypeAction::kSelect, requested_route_->get_target(), "");
	//get_current_query_actions()->ExecuteQuery_();

	response.setStatus(HTTPResponse::HTTP_OK);
	response.setContentType("application/json");

	std::ostream& out = response.send();
	out << "{GET}";
	out.flush();
}

void BusinessHandler::HandlePOSTMethod_(HTTPServerRequest& request, HTTPServerResponse& response)
{
	get_current_query_actions()->IdentifyFilters_();
	get_current_query_actions()->ComposeQuery_(TypeAction::kInsert, requested_route_->get_target(), "");

	response.setStatus(HTTPResponse::HTTP_OK);
	response.setContentType("application/json");

	std::ostream& out = response.send();
	out << "{POST}";
	out.flush();
}

void BusinessHandler::HandlePUTMethod_(HTTPServerRequest& request, HTTPServerResponse& response)
{
	get_current_query_actions()->IdentifyFilters_();
	get_current_query_actions()->ComposeQuery_(TypeAction::kUpdate, requested_route_->get_target(), "");

	response.setStatus(HTTPResponse::HTTP_OK);
	response.setContentType("application/json");

	std::ostream& out = response.send();
	out << "{PUT}";
	out.flush();
}

void BusinessHandler::HandleDELMethod_(HTTPServerRequest& request, HTTPServerResponse& response)
{
	get_current_query_actions()->IdentifyFilters_();
	get_current_query_actions()->ComposeQuery_(TypeAction::kDelete, requested_route_->get_target(), "");

	response.setStatus(HTTPResponse::HTTP_OK);
	response.setContentType("application/json");

	std::ostream& out = response.send();
	out << "{DEL}";
	out.flush();
}

void BusinessHandler::AddRoutes_()
{
	get_routes_list().push_back(new Route("business",std::vector<std::string>{"api", get_api_verion(), "business"}));
	get_routes_list().push_back(new Route("users",std::vector<std::string>{"api", get_api_verion(), "business", "users"}));
	get_routes_list().push_back(new Route("actions",std::vector<std::string>{"api", get_api_verion(), "business", "users", "actions"}));
	get_routes_list().push_back(new Route("permissions",std::vector<std::string>{"api", get_api_verion(), "business", "permissions"}));
	get_routes_list().push_back(new Route("permissions_log",std::vector<std::string>{"api", get_api_verion(), "business", "permissions", "permissions_log"}));
	get_routes_list().push_back(new Route("levels",std::vector<std::string>{"api", get_api_verion(), "business", "levels"}));
	get_routes_list().push_back(new Route("levels_log",std::vector<std::string>{"api", get_api_verion(), "business", "levels", "levels_log"}));
	get_routes_list().push_back(new Route("banks_accounts",std::vector<std::string>{"api", get_api_verion(), "business", "banks_accounts"}));
	get_routes_list().push_back(new Route("transactions",std::vector<std::string>{"api", get_api_verion(), "business", "banks_accounts", "transactions"}));
}
