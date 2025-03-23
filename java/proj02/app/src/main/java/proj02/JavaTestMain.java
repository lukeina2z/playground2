package proj02;

class Animal {
    public int age;

    public Animal(int age) {
        this.age = age;
    }

    public void sayHi() {
        System.out.println("Hi guy! " + this.age);
    }
}

public class JavaTestMain {
    public static void test(final Animal animal) {
        animal.age += 20;
        animal.sayHi();
    }

    public static void main(String[] args) {
        Animal animal = new Animal(5);
        test(animal);
    }
}