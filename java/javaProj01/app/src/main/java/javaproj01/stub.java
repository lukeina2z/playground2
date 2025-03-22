package javaproj01;

public class stub {
    public static void main(String[] args) {
        System.out.println("Hello from stub::main().");

        IAnimal cat = new Cat();
        IAnimal dog = new Dog();
        
        cat.drink(); // Outputs: Cat is drinking milk
        dog.drink(); // Outputs: Dog is drinking water

        String strBar = "null";
        java.util.Optional<String> optStr = java.util.Optional.ofNullable(strBar);
        if (optStr.isPresent())
        {
            System.out.println("present.");
        }
        else
        {
            System.out.println("not present.");
        }


        System.out.println("End of stub::main().");
    }
}
