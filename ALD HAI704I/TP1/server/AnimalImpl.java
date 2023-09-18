package server;

import commons.Animal;

import java.rmi.server.UnicastRemoteObject;

    public static class AnimalImpl extends UnicastRemoteObject implements Animal {
        String nom;
        String nomProprio;
        String race;
        String espece;

        }
}
