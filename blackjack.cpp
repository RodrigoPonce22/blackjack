#include "rlutil.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <conio.h>

using namespace std;

void mezcla (bool cartasdadas[]);
void moscarta (int carta);
void moscarta (int mano[], const int contcartas);
int nuevacarta(bool cartasdadas[]);
int puntajemano(int mano[], const int contcartas);
void mostrarmanosypuntos(int manocasa[], const int icontcartascasa, int manojugador[], const int contarcartasjugador);
void mostrarpuntosauto (int manomaquina [], const int contcartmaquina);
void automezcla (bool cartasauto[]);



int main()
{
    int opcion,fin=1,seguirj;
        rlutil::setColor(15);
        gotoxy(5,2);
        cout<<"************************************************ ACLARACIONES ************************************************";
        gotoxy(32,4);
        cout<<" 1-Las decisiones que se tomen deberan ser con mayusculas";
        gotoxy(32,6);
        cout<<" 2-El nombre del jugador no debe contener espacios"<<endl<<endl;
        gotoxy(38,8);
        system("PAUSE");
        rlutil::cls();
    do
    {
        seguirj=1;
        gotoxy(7,2);
        cout <<"----------------------------------------------------------------------------------------------------------"<<endl;
        gotoxy(7,3);
        cout <<"-                                               BLACKJACK 21                                             -"<<endl;
        gotoxy(7,4);
        cout <<"----------------------------------------------------------------------------------------------------------"<<endl;
        rlutil::setColor(11);
        gotoxy(7,6);
        cout<<"=================================================== MENU =================================================";
        gotoxy(53,8);
        cout<<"1- Nuevo Juego";
        gotoxy(53,10);
        cout<<"2- Juego automatico";
        gotoxy(53,12);
        cout<<"3- Reglas";
        gotoxy(53,14);
        cout<<"4- Creditos";
        gotoxy(53,16);
        cout<<"0- Cerrar programa";
        rlutil::setColor(15);
        gotoxy(53,18);
        cout<<"Seleccione una opcion: ";
        cin>>opcion;
        rlutil::cls();
        switch (opcion)
        {
        case 1:
        {
            rlutil::setColor(10);
            gotoxy(0,2);
            cout<<"ESCRIBA EL NOMBRE DEL JUGADOR: ";
            rlutil::setColor(15);
            char nombrejugador[50];
            cin>> nombrejugador;
            rlutil::cls();
            cout<<endl;
            ///INICIA EL GENERADOR RANDOM DE NUMEROS
            time_t qtime;
            time(&qtime);
            srand (qtime);

            bool cartasdadas[52];
            int contcartascasa = 0;
            int manocasa[12];
            int contarcartasjugador = 0;
            int manojugador[12];

            ///UNA VUELTA POR CADA MANO
            while (seguirj!=0)
            {

                mezcla(cartasdadas);
                manojugador[0] = nuevacarta(cartasdadas);
                manocasa[0] = nuevacarta(cartasdadas);
                manojugador[1] = nuevacarta(cartasdadas);
                manocasa[1] = nuevacarta(cartasdadas);
                contcartascasa = 2;
                contarcartasjugador = 2;

                rlutil::setColor(14);
                gotoxy(0,2);
                cout <<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                gotoxy(0,3);
                cout <<"-                                                       NUEVA MANO                                                     -"<<endl;
                gotoxy(0,4);
                cout <<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                rlutil::setColor(15);
                cout<<endl;
                char eleccionjugador;
                bool jugadorpide = true;
                int puntosjugador = puntajemano(manojugador,contarcartasjugador);
                ///SI EL JUGADOR PIDE CALCULA EL PUNTAJE Y VUELVE A MOSTRAR DESPUES DE CADA PEDIDO
                do
                {
                    ///MUESTRA LA CARTA DADA AL JUGADOR, PERO SOLO LA 2? CARTA DE LA CASA
                    cout<<"MANO DE LA CASA"<<endl;
                    moscarta(manocasa[1]);
                    cout<<"MANO DE "<<nombrejugador<<" (PUNTAJE): " <<puntajemano(manojugador,contarcartasjugador)<<endl;
                    moscarta(manojugador,contarcartasjugador);
                    cout<<"TE QUEDAS (Q) O PEDIS OTRA CARTA (P)?: ";
                    cin>> eleccionjugador;
                    if(eleccionjugador== 'P')
                    {
                        manojugador[contarcartasjugador] = nuevacarta(cartasdadas);
                        ++contarcartasjugador;
                    }
                    else if (eleccionjugador == 'Q')
                    {
                        jugadorpide = false;
                    }
                    else
                    {
                        cout<< "POR ACA NO ES CAPO"<<endl;
                    }
                    cout<<endl;
                    ///TOMA EL PUNTAJE DEL JUGADOR Y SE FIJA QUE NO PASO DE 21
                    puntosjugador = puntajemano(manojugador,contarcartasjugador);
                }
                while (jugadorpide && puntosjugador < 22);

                if(jugadorpide > 21)
                {
                    ///EL JUGADOR SE PASO, GANA LA CASA
                    cout<< "*****GANO LA CASA*****"<<endl;
                    mostrarmanosypuntos(manocasa,contcartascasa,manojugador, contarcartasjugador);
                }
                else
                {
                    ///SI EL JUGADOR NO SE PASO, LA CASA PIDE OTRA CARTA SIEMPRE QUE NO TENGA MAS DE 17 PUNTOS
                    int puntajecasa = puntajemano (manocasa,contcartascasa);
                    while(puntajecasa < 17)
                    {
                        manocasa[contcartascasa]= nuevacarta(cartasdadas);
                        ++contcartascasa;
                        puntajecasa = puntajemano (manocasa,contcartascasa);
                    }
                    bool muchacasa = (puntajecasa > 21 && puntosjugador < 22);
                    if (muchacasa)
                    {
                        ///la casa se paso de 21 asi que gana el jugador
                        cout<<"*****GANASTE COMPA*****"<<endl;
                        mostrarmanosypuntos(manocasa,contcartascasa,manojugador,contarcartasjugador);
                    }
                    else
                    {
                        if (puntosjugador == puntajecasa)
                        {
                            cout<<"*****UN EMPATE, NADIE GANA*****"<<endl;
                            mostrarmanosypuntos (manocasa,contcartascasa,manojugador,contarcartasjugador);
                        }
                        else if (puntosjugador > puntajecasa && puntosjugador < 21)
                        {
                            cout<<"*****GANASTE COMPA*****"<<endl;
                            mostrarmanosypuntos (manocasa,contcartascasa,manojugador,contarcartasjugador);
                        }
                        else
                        {
                            cout<< "*****GANO LA CASA*****"<<endl;
                            mostrarmanosypuntos (manocasa,contcartascasa,manojugador,contarcartasjugador);
                        }
                    }
                }
                cout<< "Seleccione una opcion"<<endl<<"1- Jugar de nuevo"<<endl<<"0- Volver al menu"<<endl;
                cin>>seguirj;
                system("PAUSE");
                rlutil::cls();
            }
        }
        break;
        case 2:
        {

            bool cartasauto[52];
            int contcartascasa = 0;
            int manocasa[12];
            int contcartmaquina = 0;
            int manomaquina[12];

            while (seguirj!=0)
            {
                automezcla(cartasauto);
                manomaquina[0] = nuevacarta(cartasauto);
                manocasa[0] = nuevacarta(cartasauto);
                manomaquina[1] = nuevacarta(cartasauto);
                manocasa[1] = nuevacarta(cartasauto);
                contcartascasa = 2;
                contcartmaquina = 2;

                rlutil::setColor(14);
                gotoxy(0,2);
                cout <<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                gotoxy(0,3);
                cout <<"-                                                  JUEGO AUTOMATICO                                                 -"<<endl;
                gotoxy(0,4);
                cout <<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                rlutil::setColor(15);

                int puntosmaquina = puntajemano(manomaquina,contcartmaquina);
                cout<<"MANO DE LA CASA"<<endl;
                moscarta(manomaquina[1]);
                cout<<endl;
                cout<<"MANO DE LA MAQUINA (PUNTAJE): " <<puntajemano(manomaquina,contcartmaquina)<<endl;
                moscarta(manomaquina,contcartmaquina);

                puntosmaquina = puntajemano(manomaquina,contcartmaquina);
                if(puntosmaquina > 21)
                {
                    ///EL JUGADOR SE PASO, GANA LA CASA
                    cout<< "*****GANO LA CASA*****"<<endl;
                    mostrarmanosypuntos(manocasa,contcartascasa,manomaquina,contcartmaquina);
                }
                else
                {
                    ///SI EL JUGADOR NO SE PASO, LA CASA PIDE OTRA CARTA SIEMPRE QUE NO TENGA MAS DE 17 PUNTOS
                    int puntajecasa = puntajemano (manocasa,contcartascasa);
                    while(puntajecasa < 17 && puntosmaquina < 16)
                    {
                        manocasa[contcartascasa]= nuevacarta(cartasauto);
                        ++contcartascasa;
                        puntajecasa = puntajemano (manocasa,contcartascasa);
                        manomaquina[contcartmaquina]= nuevacarta(cartasauto);
                        ++contcartmaquina;
                        puntosmaquina = puntajemano(manomaquina,contcartmaquina);
                    }
                    bool muchacasa = (puntajecasa > 21 && puntosmaquina < 22);
                    if (muchacasa)
                    {
                        ///la casa se paso de 21 asi que gana el jugador
                        cout<<"*****GANO LA MAQUINA*****"<<endl;
                        mostrarmanosypuntos(manocasa,contcartascasa,manomaquina,contcartmaquina);
                    }
                    else
                    {
                        if (puntosmaquina == puntajecasa)
                        {
                            cout<<"*****UN EMPATE, NADIE GANA*****"<<endl;
                            mostrarmanosypuntos (manocasa,contcartascasa,manomaquina,contcartmaquina);
                        }
                        else if (puntosmaquina > puntajecasa && puntosmaquina < 21)
                        {
                            cout<<"*****GANO LA MAQUINA*****"<<endl;
                            mostrarmanosypuntos (manocasa,contcartascasa,manomaquina,contcartmaquina);
                        }
                        else
                        {
                            cout<< "*****GANO LA CASA*****"<<endl;
                            mostrarmanosypuntos (manocasa,contcartascasa,manomaquina,contcartmaquina);
                        }
                    }
                }
                cout<< "Seleccione una opcion"<<endl<<"1- Jugar de nuevo"<<endl<<"0- Volver al menu"<<endl;
                cin>>seguirj;
                rlutil::cls();
            }
            break;
        }
         case 3:
        {
            rlutil::setColor(11 );
            cout<<endl<<"      *+*+*+*+*+*+*+*+*+*+*+*+*+*+*+ REGLAS *+*+*+*+*+*+*+*+*+*+*+*+*+*+*+"<<endl<<endl;
            cout<<"El objetivo es simple:Ganarle a la casa obteniendo el puntaje m?s cercano a 21. Las figuras (el comodin (J),el valet (T), la Reina (Q) y el Rey(K)) valen 10, el As vale 11 o 1 y todas las otras cartas conservan su valor"<<endl<<endl;
        }
        rlutil::setColor(15);
        system("PAUSE");
        rlutil::cls();
        break;
        case 4:
        {
            rlutil::setColor(11);
            cout<<"*+*+*+*+*+*+*+*+*+ CREDITOS *+*+*+*+*+*+*+*+*+"<<endl<<endl;
            cout<<"                  CREADO POR                   "<<endl<<endl;
            rlutil::setColor(15);
            cout<<"              Cesar ";
            rlutil::setColor(14);
            cout<<"Ignacio";
            rlutil::setColor(15);
            cout<<" Gomez "<<endl<<endl;
            cout<<"              Rodrigo ";
            rlutil::setColor(14);
            cout<<"Ruben";
            rlutil::setColor(15);
            cout<<" Ponce "<<endl<<endl;
            rlutil::setColor(11);
            cout<<"           Blas Agustin Leiva Eljall "<<endl<<endl;
            cout<<"                  Angel Lopez "<<endl<<endl;
            cout<<"*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+"<<endl<<endl;
            rlutil::setColor(15);
            system("pause");
            rlutil::cls();
        }
        break;
        case 0:
        {
            fin=0;
        }
        break;
        default:
        {
            cout<<"POR ACA NO FLACO";
        }
        break;

        }
    }
    while(fin!=0);
    return 0;

}
///MEZCLA LAS CARTAS
void mezcla(bool cartasdadas[])
{
    for (int iIndex = 0; iIndex < 52; ++iIndex)
    {
        cartasdadas[iIndex] = false;
    }
}
///MEZCLA LAS CARTAS DE LA VERSION AUTOMATICA
void automezcla(bool cartasauto[])
{
    for (int index = 0; index < 52; ++index)
    {
        cartasauto[index]= false;
    }
}

void moscarta(int carta)
{
    using namespace std;
    ///MUESTRA EL RANGO DE LAS CARTAS
    const int rango = (carta % 13);
    if (rango == 0)
    {
        cout << 'A';
    }
    else if (rango < 9)
    {
        cout << (rango + 1);
    }
    else if ((rango) == 9)
    {
        cout << 'T';
    }
    else if (rango == 10)
    {
        cout << 'J';
    }
    else if (rango == 11)
    {
        cout << 'Q';
    }
    else
    {
        cout << 'K';
    }
    ///MUESTRA LOS TIPOS DE CARTAS
    const int tipos = (carta/13);
    if (tipos == 0)
    {
        cout << 'T';
    }
    else if (tipos == 1)
    {
        cout << 'D';
    }
    else if (tipos == 2)
    {
        cout << 'C';
    }
    else
    {
        cout << 'P';
    }
}

///MOSTRAR LA SIGUIENTE CARTA
void moscarta(int mano[], const int contcartas)
{
    using namespace std;
    for (int cartasindex = 0; cartasindex < contcartas; ++cartasindex)
    {
        const int siguientecarta = mano[cartasindex];
        moscarta(siguientecarta);
        cout << " ";
    }
    cout << endl;
}

///ELIGE LA SIGUIENTE CARTA
int nuevacarta(bool cartasdadas[])
{
    bool cartadada    = true;
    int cartanueva    = -1;
    do
    {
        cartanueva = (rand() % 52);
        if (!cartasdadas[cartanueva])
        {
            cartadada = false;
        }
    }
    while (cartadada);
    return cartanueva;
}

///CALCULA EL PUNTAJE DE LA MANO
int puntajemano(int mano[], const int contcartas)
{
    int contace    = 0;
    int puntaje        = 0;
    for (int cartasindex = 0; cartasindex < contcartas; ++cartasindex)
    {
        const int cartanueva = mano[cartasindex];
        const int rango = (cartanueva % 13);
        if (rango == 0)
        {
            ++contace;
            ++puntaje;
        }
        else if (rango < 9)
        {
            puntaje = puntaje + (rango + 1);
        }
        else
        {
            puntaje = puntaje + 10;
        }
    }
    while (contace > 0 && puntaje < 12)
    {
        --contace;
        puntaje = puntaje + 10;
    }
    return puntaje;
}
///MUESTRA LOS PUNTAJES FINALES
void mostrarmanosypuntos(int manocasa[], const int icontcartascasa, int manojugador[], const int contarcartasjugador)
{
    using namespace std;
    cout << "PUNTAJE DE LA CASA = " << puntajemano(manocasa, icontcartascasa) << endl;
    moscarta(manocasa, icontcartascasa);
    cout << "PUNTAJE DEL JUGADOR = " << puntajemano(manojugador, contarcartasjugador) << endl;
    moscarta(manojugador, contarcartasjugador);
    cout << endl;

}
