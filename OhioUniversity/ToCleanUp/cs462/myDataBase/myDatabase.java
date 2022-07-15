/****************************************************************/
/* GradeBook Application Main class (Section 5.6)               */
/* Needs grade1.java and grade2.java to be compiled             */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.io.*; 
import java.sql.*;

class myDatabase { 

  public static void main (String args []) 
      throws SQLException, IOException { 

    army1 a1 = new army1();
    boolean done;
    char ch,ch1;
    byte num = 0;

    try {
      Class.forName ("oracle.jdbc.driver.OracleDriver");
    } catch (ClassNotFoundException e) {
        System.out.println ("Could not load the driver");
        return;
      }
    String user, pass;
    user = readEntry("userid  : ");
    pass = readEntry("password: ");

    //  The following line was modified by Prof. Marling to work on prime

    Connection conn = DriverManager.getConnection
       ("jdbc:oracle:thin:@deuce.cs.ohiou.edu:1521:class", user, pass);

    done = false;
    do {
      a1.print_menu();
      System.out.print("Type in your option:");
      System.out.flush();
      ch = (char) System.in.read();
      ch1 = (char) System.in.read();
      switch (ch) {
        case '1' : a1.add_soldier(conn);
                   break;
        case '2' : a1.add_equipment(conn);
                   break;
        case '3' : a1.add_mission(conn);
                   break;
        case '4' : a1.drop_soldier(conn);
                   break;
        case '5' : a1.drop_equipment(conn);
                   break;
        case '6' : a1.drop_mission(conn);
                   break;
        case '7' : a1.show_soldiers(conn);
                   break;
        case '8' : a1.show_equipment(conn);
                   break;
        case '9' : a1.show_missions(conn);
                   break;
        case 'a' : a1.modify_soldier(conn);
                   break;
        case 'b' : a1.modify_equipment(conn);
                   break;
        case 'c' : a1.modify_mission(conn);
                   break;
        case 'd' : a1.print_cost_per_Soldier(conn);
                   break;
        case 'e' : a1.print_mission_report(conn);
                   break;
        case 'q' : done = true;
                   break;
        default  : System.out.println("Type in option again");
      }
    } while (!done);

    conn.close();
  }

  //readEntry function -- to read input string
  static String readEntry(String prompt) {
     try {
       StringBuffer buffer = new StringBuffer();
       System.out.print(prompt);
       System.out.flush();
       int c = System.in.read();
       while(c != '\n' && c != -1) {
         buffer.append((char)c);
         c = System.in.read();
       }
       return buffer.toString().trim();
     } catch (IOException e) {
       return "";
       }
   }
} 

