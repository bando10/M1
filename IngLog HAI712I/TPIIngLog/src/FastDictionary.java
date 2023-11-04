public class FastDictionary extends AbstractDico {
	
	FastDictionary(){
		super();
	}

	public boolean mustGrow(){
		return (this.size() > 0.75*this.size || this.size == 0);
	}
	@Override
	public int indexOf(Object Key) {
		int hash = Key.hashCode();
		hash = Math.abs(hash);
		int i = hash % this.size;
		do {
			i = ((i+1) % this.size);
		}while(keys[i] != Key);
		return i;
	}

	@Override
	public int newIndexOf(Object Key) {
		if(this.mustGrow()) {
			this.grow();
		}
		int hash = Key.hashCode();
		hash = Math.abs(hash);
		int i = hash % this.size;
		if(keys[i] == null) {
			return i;
		}else {
			do {
				System.out.println("Conflit avec Methode Hash");
				i = ((i+1) % this.size);
			}while(keys[i] != null);
		}
		return i;
	}
	
	@Override
	public int size() {
		int n = 0;
		for(Object e : this.keys) {
			n++;
		}
		return n;
	}
	
	public void grow() {
		System.out.println("Tableau trop petit, on procède à un agrandissement !");
		int n = this.size == 0 ? 20 : 2*this.size ;
		Object[] newKeys = new Object[n];
		Object[] newValues = new Object[n];
		for(int i=0; i < n - 1; i++) {
			newKeys[i] = this.keys[i];
			newValues[i] = this.values[i];
		}
		this.keys = newKeys;
		this.values = newValues;
		this.size = n;
	}
}
