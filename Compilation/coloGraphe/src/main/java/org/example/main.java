// Binome: Sio Bando et Tony Nguyen


package org.example;

import java.util.ArrayList;

import static org.example.main.ANSI_RESET;
import static org.example.main.COLOR;


class Vertex {
    int color = -1;
    int name;

    Vertex(int name){
        this.name = name;
    }

    public int getColor() {
        return color;
    }

    public void setColor(int color) {
        this.color = color;
    }

    @Override
    public String toString() {
        return name + "  coloré avec  " + color;
    }
}

class Edge {
    Vertex vertices[] = new Vertex[2];

    Edge(Vertex s1, Vertex s2){
        this.vertices[0] = s1;
        this.vertices[1] = s2;
    }

    public boolean estDans(Vertex s) {
        return (vertices[0].equals(s)|| vertices[1].equals(s));
    }

    @Override
    public String toString() {
        return "Edge entre " + vertices[0].toString() + " et " + vertices[1].toString();
    }
}

class Graph{
    private ArrayList<Vertex> vertices;
    private ArrayList<Edge> edges;
    private ArrayList<Edge> pref;

    public Graph(ArrayList<Vertex> vertices, ArrayList<Edge> edges, ArrayList<Edge> pref) {
        this.vertices = vertices;
        this.edges = edges;
        this.pref = pref;
    }

    public Graph(ArrayList<Vertex> vertices, ArrayList<Edge> edges) {
        this.vertices = vertices;
        this.edges = edges;
    }

    public ArrayList<Vertex> getVertices() {
        return vertices;
    }

    public ArrayList<Edge> getEdges() {
        return edges;
    }

    public void setVertices(ArrayList<Vertex> vertices) {
        this.vertices = vertices;
    }

    public void setEdges(ArrayList<Edge> edges) {
        this.edges = edges;
    }

    public void setPref(ArrayList<Edge> pref) {
        this.pref = pref;
    }

    public int degre(Vertex s) {
        int d = 0;
        for (Edge e : edges) {
            if (e.estDans(s)) {
                d++;
            }
        }
        return d;
    }

    public boolean coloriable(Vertex s, int color){
        for(Edge e : edges){
            if(e.estDans(s)){
                if(e.vertices[0].getColor() == color||e.vertices[1].getColor() == color){
                    return false;
                }
            }
        }
        return true;
    }

    private int prefCol(Vertex s){
        for(Edge e : pref){
            if(e.estDans(s)){
                if(e.vertices[0].equals(s)){
                    if(e.vertices[1].getColor() != -1){
                        return e.vertices[1].getColor();
                    }
                } else {
                    if(e.vertices[0].getColor() != -1){
                        return e.vertices[0].getColor();
                    }
                }
            }
        }
        return -1;}

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for(Vertex s : vertices){
            int modcol = s.color%9;
            if (s.color != -1){sb.append(COLOR).append(String.valueOf(modcol)).append("m +");}

            sb.append("Vertex ");
            sb.append(s.name);
            sb.append(" couleur: ");
            sb.append(s.color);
            if (s.color != -1){sb.append(ANSI_RESET);}
            sb.append("\n");
        }
        return sb.toString();
    }
    }

public class main {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String COLOR = "\u001B[3";
    public static void main(String[] args) {

        //Création graphes

        Vertex u, t, v, x, y, z;

        u = new Vertex(15);
        t = new Vertex(10);
        v = new Vertex(11);
        x = new Vertex(12);
        y = new Vertex(13);
        z = new Vertex(14);
        Edge e10 = new Edge(x,z);
        Edge e11 = new Edge(y,z);
        Edge e12 = new Edge(y,t);
        Edge e20 = new Edge(x,z);
        Edge e21 = new Edge(y,z);
        Edge e22 = new Edge(y,t);
        Edge e23 = new Edge(t,u);
        Edge e24 = new Edge(v,z);
        ArrayList<Edge> listEdgeInterf = new ArrayList<>();
        listEdgeInterf.add(e20);
        listEdgeInterf.add(e21);
        listEdgeInterf.add(e22);
        listEdgeInterf.add(e23);
        listEdgeInterf.add(e24);
        ArrayList<Edge> listEdgePref = new ArrayList<>();

        listEdgePref.add(e10);
        listEdgePref.add(e11);
        listEdgePref.add(e12);
        ArrayList<Vertex> listVertex = new ArrayList<>();
        listVertex.add(t);
        listVertex.add(v);
        listVertex.add(u);
        listVertex.add(x);
        listVertex.add(y);
        listVertex.add(z);
        Graph g = new Graph(listVertex, listEdgeInterf, listEdgePref);
        colorGraph(g, 2);System.out.println(g);
        g = new Graph(listVertex, listEdgeInterf, listEdgePref);
        colorGraph(g, 3);
        System.out.println(g);
    }
    private static void colorGraph(Graph graph, int k) {
        for(Vertex s : graph.getVertices()){
            if(s.getColor() == -1){
                for(int i = 1; i <= k; i++){
                    if(graph.coloriable(s,i)){
                        s.setColor(i);
                    }
                }
            }
        }
    }
}



