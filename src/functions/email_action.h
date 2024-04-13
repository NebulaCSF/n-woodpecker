
#ifndef FUNCTIONS_EMAIL_ACTION
#define FUNCTIONS_EMAIL_ACTION


#include <string>
#include <vector>

#include "Poco/Net/MailMessage.h"
#include "Poco/Net/MailRecipient.h"
#include "Poco/Net/SecureSMTPClientSession.h"
#include "Poco/Net/StringPartSource.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/SharedPtr.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"

#include "functions/action.h"


namespace Atom
{
    namespace Functions
    {
        class SSLInitializer;
        class EmailAction;
    }
}

using namespace Poco;
using namespace Poco::Util;



class Atom::Functions::SSLInitializer
{
    public:
        SSLInitializer()
        {
            Poco::Net::initializeSSL();
        }
        
        ~SSLInitializer()
        {
            Poco::Net::uninitializeSSL();
        }
};

class Atom::Functions::EmailAction : public Atom::Functions::Action
{
    public:
        EmailAction(std::string identifier);

        std::string get_mail_host() const { return mail_host_; }
        std::string get_sender() const { return sender_; }
        std::string get_recipient() const { return recipient_; }
        std::string get_subject() const { return subject_; }
        std::string get_email_message() const { return email_message_; }
        std::string get_email_user() const { return email_user_; }
        std::string get_email_password() const { return email_password_; }

        void set_mail_host(std::string mail_host) { mail_host_ = mail_host; };
        void set_sender(std::string sender) { sender_ = sender; };
        void set_recipient(std::string recipient) { recipient_ = recipient; };
        void set_subject(std::string subject) { subject_ = subject; };
        void set_email_message(std::string email_message) { email_message_ = email_message; };
        void set_email_user(std::string email_user) { email_user_ = email_user; };
        void set_email_password(std::string email_password) { email_password_ = email_password; };

        virtual bool Work_();

    protected:
        void UpdateDataMembers_();
        void UpdateMessageParameters_();

    private:
        std::string mail_host_;
        std::string sender_;
        std::string recipient_;
        std::string subject_;
        std::string email_message_;
        std::string email_user_;
        std::string email_password_;
};

#endif // FUNCTIONS_EMAIL_ACTION
