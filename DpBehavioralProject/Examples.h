#pragma once
#include <iostream>
#include "Iterator.h"
#include "Strategy.h"
#include "ChainOfResponsibility.h"
#include "Command.h"
#include "Mediator.h"


class Examples
{
public:
	static void Iterator()
	{
        Matrix matrix(4, 5);

        for (int i{}; i < matrix.Rows(); i++)
            for (int j{}; j < matrix.Columns(); j++)
                matrix(i, j) = (i + 1) * 10 + (j + 1);

        for (int i{}; i < matrix.Rows(); i++)
        {
            for (int j{}; j < matrix.Columns(); j++)
                std::cout << matrix(i, j) << " ";
            std::cout << "\n";
        }

        auto hi = matrix.HMatrixIterator();

        for (hi->Set(); !hi->IsDone(); hi->Next())
            std::cout << hi->Current() << " ";

        std::cout << "\n";

        auto vi = matrix.VMatrixIterator();
        for (vi->Set(); !vi->IsDone(); vi->Next())
            std::cout << vi->Current() << " ";

        std::cout << "\n";
	}

    static void Strategy()
    {
        srand(time(nullptr));

        Vector myv(10);
        for (int i{}; i < myv.V().size(); i++)
            myv.V()[i] = rand() % 100;

        for (int i{}; i < myv.V().size(); i++)
            std::cout << myv.V()[i] << " ";
        std::cout << "\n";

        myv.SetStrategy(new SelectSortStrategy());
        myv.Sort();

        for (int i{}; i < myv.V().size(); i++)
            std::cout << myv.V()[i] << " ";
        std::cout << "\n";
    }

    static void Chain()
    {
        Receiver* bobby = new Receiver(true, true, false);
        Receiver* yandex = new Receiver(true, false, true);
        Receiver* tbank = new Receiver(false, false, true);
        Receiver* bankrot = new Receiver(false, false, false);


        PaymentHandler* payShop = new EpayTransferHandler();
        payShop->SetSuccessor(new CashTransferHandler());
        payShop->SetSuccessor(new BankTransferHandler());
        /*payShop->SetSuccessor(new BankTransferHandler())
            ->SetSuccessor(new EpayTransferHandler());*/

        payShop->Handle(bobby);
        std::cout << "\n";
        payShop->Handle(yandex);
        std::cout << "\n";
        payShop->Handle(tbank);
        std::cout << "\n";
        payShop->Handle(bankrot);
    }

    static void Command()
    {
        Television* tv = new Television();

        Controller* pult = new Controller(
            new TvOnCommand(tv),
            new TvSoundUpCommand(tv),
            new TvSoundDownCommand(tv));

        pult->PowerButton();
        pult->PlusButton();
        pult->PlusButton();
        pult->MinusButton();
        pult->UndoButton();
    }

    static void Mediator()
    {
        ProjectManager* manager = new ProjectManager();
        Collegue* customer = new CustomerCollegue(manager);
        Collegue* developer = new DeveloperCollegue(manager);
        Collegue* tester = new TesterCollegue(manager);

        manager->Customer() = customer;
        manager->Developer() = developer;
        manager->Tester() = tester;

        customer->Send("Order! I need application!");
        developer->Send("Program is ready!");
        tester->Send("Application is tested and ready");
    }
};

