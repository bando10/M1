package dictionary;

public class FastDictionary extends AbstractDico {
    FastDictionary() {
        super();
    }

    @Override
    int indexOf(Object Key) {
        int hash = Key.hashCode();
        hash = Math.abs(hash);
        int i = hash % this.size();
        do {
            i = ((i+1) % this.size());
        } while (keys[i] != Key);
        return i;
    }

    @Override
    int newIndexOf(Object Key) {
        if (this.size() > 0.75 * this.size() || this.size() == 0){
            this.grow();
        }
        int hash = Key.hashCode();
        hash = Math.abs(hash);
        int i = hash % this.size;
        if (keys[i] == null){
            return i;
        } else {
            do {
                System.out.println("Conflit methode Hash\n");
                i = ((i+1) % this.size());
            } while (keys[i] != null);
        }
        return i;
    }

    public int size() {
        int n = 0;
        for (Object e : this.keys){
            n++;
        }
        return n;
    }

    void grow() {
        System.out.println("grow() car tableau trop petit\n");
        int n = this.size() == 0? 20 : 2*this.size();
        Object[] newKeys = new Object[n];
        Object[] newValues = new Object[n];
        for (int i = 0; i < n-1; i++){
            newKeys[i] = this.keys[i];
            newValues[i] = this.values[i];
        }
        this.keys = newKeys;
        this.values = newValues;
        this.size = n;
    }
}