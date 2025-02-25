interface Explorer {
    void explore();
}

abstract class Planet implements Explorer {
    String name;

    Planet(String name) {
        this.name = name;
    }

    void planetInfo() {
        System.out.println("Exploring planet: " + name);
    }
}

class Mars extends Planet {
    Mars() {
        super("Mars");
    }

    public void explore() {
        System.out.println("Exploring Mars: Searching for signs of ancient water and microbial life.");
    }
}

class Venus extends Planet {
    Venus() {
        super("Venus");
    }

    public void explore() {
        System.out.println("Exploring Venus: Studying its thick atmosphere and volcanic surface.");
    }
}

class Saturn extends Planet {
    Saturn() {
        super("Saturn");
    }

    public void explore() {
        System.out.println("Exploring Saturn: Analyzing its rings and giant storms.");
    }
}

public class p9 {
    public static void main(String[] args) {
        Planet mars = new Mars();
        Planet venus = new Venus();
        Planet saturn = new Saturn();

        mars.planetInfo();
        mars.explore();
        System.out.println();

        venus.planetInfo();
        venus.explore();
        System.out.println();

        saturn.planetInfo();
        saturn.explore();
    }
}

