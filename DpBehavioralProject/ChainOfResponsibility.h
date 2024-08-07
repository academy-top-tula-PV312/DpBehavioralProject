#pragma once
#include <iostream>

class Receiver
{
	bool bankTransfer;
	bool cashTransfer;
	bool epayTransfer;
public:
	bool& BankTransfer() { return bankTransfer; }
	bool& CashTransfer() { return cashTransfer; }
	bool& EpayTransfer() { return epayTransfer; }

	Receiver(bool bankTransfer, bool cashTransfer, bool epayTransfer)
		: bankTransfer{ bankTransfer },
		cashTransfer{ cashTransfer },
		epayTransfer{ epayTransfer } {}
};

class PaymentHandler
{
	PaymentHandler* successor{ nullptr };
public:
	PaymentHandler*& Successor() { return successor; }

	PaymentHandler* SetSuccessor(PaymentHandler* successor)
	{
		if (this->successor)
			this->successor->SetSuccessor(successor);
		else
			this->successor = successor;
		
		return successor;
	}

	virtual void Handle(Receiver* receiver) = 0;

};

class BankTransferHandler : public PaymentHandler
{
public:
	void Handle(Receiver* receiver) override
	{
		if (receiver->BankTransfer())
			std::cout << "Bank transfer is ok\n";
		else if (this->Successor())
		{
			std::cout << "Bank transfer is not ok\n";
			this->Successor()->Handle(receiver);
		}
	}
};

class CashTransferHandler : public PaymentHandler
{
public:
	void Handle(Receiver* receiver) override
	{
		if (receiver->CashTransfer())
			std::cout << "Cash transfer is ok\n";
		else if (this->Successor())
		{
			std::cout << "Cash transfer is not ok\n";
			this->Successor()->Handle(receiver);
		}
	}
};

class EpayTransferHandler : public PaymentHandler
{
public:
	void Handle(Receiver* receiver) override
	{
		if (receiver->EpayTransfer())
			std::cout << "EPay transfer is ok\n";
		else if (this->Successor())
		{
			std::cout << "EPay transfer is not ok\n";
			this->Successor()->Handle(receiver);
		}
	}
};