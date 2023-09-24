package dictionary;

/*
public interface IDictionary{


    public Object get(Object key){  //rend la valeur associee a key dans le receveur.

    }
    public IDictionary put(Object key, Object value){ //entre une nouveau couple cle-valeur dans le receveur, rend le receveur.

    }
    public boolean isEmpty() { //rend vrai si le receveur est vide, faux sinon
    }

    public boolean containsKey(Object key) { //rend vrai si la cl´e est connue dans le receveur, faux sinon.

    }

    public int size() { //rend le nombre d’elements (donc le nombre de couples cl´e-valeur) contenus dans le receveur.

    }


}*/

public abstract class AbstractDico implements IDictionary{
    protected int size;
    protected Object[] keys;
    protected Object[] values;

    AbstractDico() {
        this.keys = new Object[0];
        this.values = new Object[0];
        this.size = 0;
    }

    // get et put

    public Object get(Object Key){
        int i = indexOf(Key);
        Object valeur = i == -1? null : values[i];
        return valeur;
    }

    public IDictionary put (Object key, Object value){
        int n = newIndexOf(Key);
        keys[n] = key;
        values[n] = value;
        return this;
    }

    //isEmpty, contains key et size
    public boolean isEmpty(){
        return this.size == 0;
    }

}
    public boolean containsKey(Object key) {
        return (indexOf(key) == -1? false : true);
    }

    public inr size(){
        return this.size;
    }
    abstract int indexOf(Object Key):
    abstract int newIndexOf(Object Key);

/*
    protected int indexOf(Object key) {
        for (int i = 0; i < keys.length; i++){
            if (keys[i].equals(key){
                return i;
            }
        }
        return -1;
    }
    protected int newIndexOf(Object key) { //augmenter taille tableau?
        if (indexOf(key).equals(-1){

        }
    }
    public Object get(Object key){
        if (indexOf(key) != -1){
            return values[indexOf(key)];}
        else {
            return -1;
        }

    public void size() {
        System.out.println( "Size == " + this.length );
    }

    public IDictionary put(Object key, Object value){
    }
    public boolean isEmpty() {
            return this.size == 0;
        }
    public booleancontainsKey(){
            return (indexOf())
        }

}

public abstract class OrderedDictionary implements IDictionary

public abstract class SortedDictionary implements IDictionary

public abstract class FastDictionary implements IDictionary


public static main({

})