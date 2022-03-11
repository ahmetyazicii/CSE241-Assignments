import java.lang.IndexOutOfBoundsException;
interface List < E > extends Collection < E >{
	E get(int index) throws IndexOutOfBoundsException;
}
