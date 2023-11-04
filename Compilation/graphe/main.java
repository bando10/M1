import java.util.ArrayList;

public class Vertex {
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

public class Edge {
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

public class Graph{
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

    public ArrayList<Sommet> getSommets() {
        return sommets;
    }

    public void setSommets(ArrayList<Sommet> sommets) {
        this.sommets = sommets;
    }

    public ArrayList<Arete> getAretes() {
        return aretes;
    }

    public void setAretes(ArrayList<Arete> aretes) {
        this.aretes = aretes;
    }

    public int degre(Vertex s) {
        int d = 0;
        for (Edge e : edges) {
            if (e.estDans(e)) {
                d++;
            }
        }
        return d;
    }

    public boolean triviallementColoriable(Vertex s, int k){
        return degre(s) < k;
    }

    public boolean coloriable?(Vertex s, int color){
        for(Edge e : edges){
            if(e.concern(s)){
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
    }

public class main {

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

    public static void main(String[] args) {

        //Création graphes
        // First test - Common graphe
        Vertex s1 = new Vertex(1);
        Vertex s2 = new Vertex(2);
        Vertex s3 = new Vertex(3);
        Vertex s4 = new Vertex(4);
        Vertex s5 = new Vertex(5);

        Edge e1 = new Edge(s1,s2);
        Edge e2 = new Edge(s1,s3);
        Edge e3 = new Edge(s2,s3);
        Edge e4 = new Edge(s3,s4);
        Edge e5 = new Edge(s2,s5);


        ArrayList<Edge> listEdgeInterf = new ArrayList<>();
        listEdgeInterf.add(e1);
        listEdgeInterf.add(e2);
        listEdgeInterf.add(e3);
        listEdgeInterf.add(e4);
        listEdgeInterf.add(e5);

        ArrayList<Vertex> listVertex = new ArrayList<>();
        listVertex.add(s1);
        listVertex.add(s2);
        listVertex.add(s3);
        listVertex.add(s4);
        listVertex.add(s5);

        Graph g = new Graph(listVertex, listEdgeInterf);
        colorGraph(g, 3);
        System.out.println(g);

        // Second test - Graph with preferences

        Vertex s6 = new Vertex(6);
        Vertex s7 = new Vertex(7);
        Vertex s8 = new Vertex(8);
        Vertex s9 = new Vertex(9);
        Vertex s14 = new Vertex(10);

        Edge e6 = new Edge(s6,s7);
        Edge e7 = new Edge(s6,s8);
        Edge e8 = new Edge(s8,s9);
        Edge e14 = new Edge(s14,s7);
        Edge e15 = new Edge(s14,s6);


        Edge e9 = new Edge(s7,s8); //Preference

        listEdgeInterf = new ArrayList<>();
        listEdgeInterf.add(e6);
        listEdgeInterf.add(e7);
        listEdgeInterf.add(e8);
        listEdgeInterf.add(e14);
        listEdgeInterf.add(e15);


        ArrayList<Edge> listEdgePref = new ArrayList<>();
        listEdgePref.add(e9);

        listVertex = new ArrayList<>();
        listVertex.add(s6);
        listVertex.add(s7);
        listVertex.add(s8);
        listVertex.add(s9);
        listVertex.add(s14);


        g = new Graph(listVertex, listEdgeInterf, listEdgePref);
        colorGraph(g, 3);
        System.out.println(g);

        // Third test - Graph with spill
        // Graph with "spill" : First print will show the pessimistic version of the algorithm, and second one will show optimistic version.

        Vertex s10 = new Vertex(10);
        Vertex s11 = new Vertex(11);
        Vertex s12 = new Vertex(12);
        Vertex s13 = new Vertex(13);

        Edge e10 = new Edge(s10,s11);
        Edge e11 = new Edge(s11,s12);
        Edge e12 = new Edge(s12,s13);
        Edge e13 = new Edge(s13,s10);

        listEdgeInterf = new ArrayList<>();
        listEdgeInterf.add(e10);
        listEdgeInterf.add(e11);
        listEdgeInterf.add(e12);
        listEdgeInterf.add(e13);

        listEdgePref = new ArrayList<>();

        listVertex = new ArrayList<>();
        listVertex.add(s10);
        listVertex.add(s11);
        listVertex.add(s12);
        listVertex.add(s13);

        g = new Graph(listVertex, listEdgeInterf, listEdgePref);

        colorGraph(g, 2);
        System.out.println(g);


    }
}



