import javax.swing.tree.TreeNode;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class BSTMain {
    public static void main(String[] args) {
        File file = new File("input1.txt");
        Scanner scn = null;
        try {
            scn = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        AVLTree avl = new AVLTree();
        while(scn.hasNextLine()){
            String data = scn.nextLine();
            // System.out.println(data);
            String command[] = data.split(" ");
            if (command[0].equalsIgnoreCase("I")){
                avl.root = avl.insertNode(avl.root, Integer.parseInt(command[1]));
                avl.printPreOrder(avl.root);
                System.out.println();
            } else if (command[0].equalsIgnoreCase("D")){
                avl.root = avl.deleteNode(avl.root, Integer.parseInt(command[1]));
                avl.printPreOrder(avl.root);
                System.out.println();
            } else if(command[0].equalsIgnoreCase("F")){
                if(avl.searchItem(avl.root, Integer.parseInt(command[1]))==null){
                    System.out.println("False");
                } else
                    System.out.println("True");
            }
        }
    }
}
