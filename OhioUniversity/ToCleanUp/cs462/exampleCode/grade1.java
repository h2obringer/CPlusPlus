/****************************************************************/
/* GradeBook Application: grade1.java (Section 5.6)             */
/* Needs grade2.java to be compiled                             */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class grade1 { 

  void print_menu() {
    System.out.println("      GRADEBOOK PROGRAM\n");
    System.out.println("(1) Add Catalog");
    System.out.println("(2) Add Course");
    System.out.println("(3) Add Students");
    System.out.println("(4) Select Course");
    System.out.println("(q) Quit\n");
  }

  void add_catalog(Connection conn) 
    throws SQLException, IOException {
         
    Statement stmt = conn.createStatement(); 

    String cnum   = readEntry("Course Number: ");
    String ctitle = readEntry("Course Title : ");
    String query = "insert into catalog values (" +
            "'" + cnum + "','" + ctitle + "')";
    try {
      int nrows = stmt.executeUpdate(query);
    } catch (SQLException e) {
        System.out.println("Error Adding Catalog Entry");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    stmt.close();
    System.out.println("Added Catalog Entry");
  }

  void add_course(Connection conn) 
        throws SQLException, IOException {

    String term_in = readEntry("Term         : ");
    String ls      = readEntry("Line Number  : ");
    String cnum    = readEntry("Course Number: ");
    String as      = readEntry("A Cutoff     : ");
    String bs      = readEntry("B Cutoff     : ");
    String cs      = readEntry("C Cutoff     : ");
    String ds      = readEntry("D Cutoff     : ");

    String query = "insert into courses values (" +
            "'" + term_in + "'," + ls + "," + 
            "'" + cnum + "'," + as + "," + 
            bs + "," + cs + "," + ds + ")";
           
    Statement stmt = conn.createStatement (); 
    try {
      stmt.executeUpdate(query);
    } catch (SQLException e) {
      System.out.println("Course was not added! Failure!");
      return;
    }
    System.out.println("Course was added! Success!");
    stmt.close();
  }

  void add_students(Connection conn) 
      throws SQLException, IOException {

    String id, ln, fn, mi;
    PreparedStatement stmt = conn.prepareStatement(
      "insert into students values (?, ?, ?, ?)"  ); 
    do {
      id = readEntry("ID (0 to stop): ");
      if (id.equals("0"))
        break;
      ln = readEntry("Last  Name    : ");
      fn = readEntry("First Name    : ");
      mi = readEntry("Middle Initial: ");
      try {
        stmt.setString(1,id);
        stmt.setString(2,fn);
        stmt.setString(3,ln);
        stmt.setString(4,mi);
        stmt.executeUpdate();
      } catch (SQLException e) {
        System.out.println("Student was not added! Error!");
      }
    } while (true);  
    stmt.close();
  }

  void select_course(Connection conn) 
    throws SQLException, IOException {

    String query1 = "select distinct lineno,courses.cno,ctitle " +
                    "from courses,catalog " +
                    "where courses.cno = catalog.cno and term = '";
    String query;
    String term_in = readEntry("Term: ");
    query = query1 + term_in + "'";
     
    Statement stmt = conn.createStatement (); 
    ResultSet rset = stmt.executeQuery(query);
    System.out.println("");
    while (rset.next ()) { 
      System.out.println(rset.getString(1) + "   " +
                         rset.getString(2) + "   " +
                         rset.getString(3));
    } 
    System.out.println("");
    String ls = readEntry("Select a course line number: ");
    
    grade2 g2 = new grade2();
    boolean done;
    char ch,ch1;

    done = false;
    do {
      g2.print_menu();
      System.out.print("Type in your option:");
      System.out.flush();
      ch = (char) System.in.read();
      ch1 = (char) System.in.read();
      switch (ch) {
        case '1' : g2.add_enrolls(conn,term_in,ls);
                   break;
        case '2' : g2.add_course_component(conn,term_in,ls);
                   break;
        case '3' : g2.add_scores(conn,term_in,ls);
                   break;
        case '4' : g2.modify_score(conn,term_in,ls);
                   break;
        case '5' : g2.drop_student(conn,term_in,ls);
                   break;
        case '6' : g2.print_report(conn,term_in,ls);
                   break;
        case 'q' : done = true;
                   break;
        default  : System.out.println("Type in option again");
      }
    } while (!done);

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

