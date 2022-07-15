/****************************************************************/
/* GradeBook Application - grade2.java (Section 5.6)            */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class grade2 { 

  void print_menu() {
    System.out.println("      SELECT COURSE SUB-MENU\n");
    System.out.println("(1) Add Students to Course");
    System.out.println("(2) Add Course Components");
    System.out.println("(3) Add Student Scores");
    System.out.println("(4) Modify Student Score");
    System.out.println("(5) Drop Student from Course");
    System.out.println("(6) Print Course Report");
    System.out.println("(q) Quit\n");
  }

  void add_enrolls(Connection conn, String term_in, String ls) 
        throws IOException, SQLException {
    String id;

    PreparedStatement stmt = conn.prepareStatement(
      "insert into enrolls values (?,'" + term_in + "',"+ls+")"  ); 

    do {
      id = readEntry("Student Id (0 to stop): ");
      if (id.equals("0"))
        break;
      try {
        stmt.setString(1,id);
        stmt.executeUpdate();
      } catch (SQLException e) {
        System.out.println("Student was not added! Error!");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }

      }
    } while (true);  
    stmt.close();
  }

  void add_course_component(Connection conn, String term_in, String ls) 
       throws SQLException, IOException {

    String cname  = readEntry("Component Name: ");
    String points = readEntry("Max. Points   : ");
    String weight = readEntry("Weight        : ");
    String query = "insert into components values (" +
            "'" + term_in + "'," + ls + "," + 
            "'" + cname + "'," + points + "," + 
            weight + ")";
           
    Statement stmt = conn.createStatement (); 
    try {
      stmt.executeUpdate(query);
    } catch (SQLException e) {
        System.out.println("Component was not added! Failure!");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
    }
    System.out.println("Component was added! Success!");
    stmt.close();
  }

  void add_scores(Connection conn, String term_in, String ls) 
    throws SQLException, IOException {

    String query = "select distinct compname " +
                   "from   courses,components " +
                   "where  courses.term = components.term and " +
                   "       courses.lineno = components.lineno and " +
                   "       courses.term = '" + term_in + "'" + " and " + 
                   "       courses.lineno = " + ls;

    Statement stmt1 = conn.createStatement (); 
    ResultSet rset1 = stmt1.executeQuery(query);
    System.out.println("");
    while (rset1.next ()) { 
      System.out.println(rset1.getString(1));
    } 
    System.out.println("");
    String cname = readEntry("Enter a component name: ");

    String query2 = "select distinct students.sid, lname, fname " +
                    "from   enrolls,students " +
                    "where  enrolls.sid = students.sid and " +
                    "       enrolls.term = '" + term_in + "'" + " and" + 
                    "       enrolls.lineno = " + ls +
                    " order by lname, fname";

    ResultSet rset2 = stmt1.executeQuery(query2);
    System.out.println("");

    PreparedStatement stmt2 = conn.prepareStatement(
      "insert into scores values (?,'"+ term_in + "'," + ls + ",'" +
       cname + "', ?)"
        ); 

    while (rset2.next ()) { 
      String pts = readEntry(cname + " Score for " + rset2.getString(1) +
                         ": " + rset2.getString(2) + ", " +
                         rset2.getString(3) + ": ");
      try {
        stmt2.setString(1,rset2.getString(1));
        stmt2.setString(2,pts);
        stmt2.executeUpdate();
      } catch (SQLException e) {
          System.out.println("Score was not added! Error!");
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
        }
    } 
    stmt1.close();
    stmt2.close();
  }

  void modify_score(Connection conn, String term_in, String ls) 
      throws SQLException, IOException {

    String id    = readEntry("Student's ID  : ");
    String cname = readEntry("Component Name: ");
    String query1 = "select points from scores where sid = '" + id +
             "' and term = '" + term_in + "' and lineno = " +
             ls + " and compname = '" + cname + "'"; 

    Statement stmt = conn.createStatement (); 
    ResultSet rset;
    try {
      rset = stmt.executeQuery(query1);
    } catch (SQLException e) {
        System.out.println("Error");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    System.out.println("");
    if ( rset.next ()  ) {
      System.out.println("Old Score = " + rset.getString(1));
      String ns = readEntry("Enter New Score: ");
      String query2 = "update scores set points = " + ns + 
                      " where sid = '" + id + "' and compname = '" +
                    cname + "' and term = '" + term_in + "' and lineno = " +
                    ls ; 
      try {
        stmt.executeUpdate(query2);
      } catch (SQLException e) {
          System.out.println("Could not modify score");
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
          return;
        }
      System.out.println("Modified score successfully");
    }
    else 
      System.out.println("Score not found");
    stmt.close();
  }

  void drop_student(Connection conn, String term_in, String ls) 
      throws SQLException, IOException {
    
    String id = readEntry("Student ID to drop: ");
    String query0 = "insert into deleted_scores " +
                    "select * from scores where sid = '" + id +
             "' and term = '" + term_in + "' and lineno = " + ls;
    String query1 = "delete scores where sid = '" + id +
             "' and term = '" + term_in + "' and lineno = " + ls;
    String query2 = "delete enrolls where sid = '" + id +
             "' and term = '" + term_in + "' and lineno = " + ls;

    conn.setAutoCommit(false);
    Statement stmt = conn.createStatement (); 
    int nrows;
    try {
      nrows = stmt.executeUpdate(query0);
      nrows = stmt.executeUpdate(query1);
      nrows = stmt.executeUpdate(query2);
    } catch (SQLException e) {
        System.out.println("Could not drop student");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        conn.rollback();
        return;
      }
    System.out.println("Dropped student");
    conn.commit();
    conn.setAutoCommit(true);
    stmt.close();
  }

  void print_report(Connection conn, String term_in, String ls) 
        throws SQLException, IOException {

    String query0 = "select a, b, c, d from courses where term = '" +
                    term_in + "' and lineno = " + ls;

    String query1 = "select compname, maxpoints, weight " +
                    "from components where term = '" + term_in + 
                    "' and lineno = " + ls;

    String query2 = "select E.sid, S.lname, S.fname " +
                    "from enrolls E, students S " +
                    "where S.sid = E.sid and " +
                    "E.term = '" + term_in + "' and " +
                    "E.lineno = " + ls +
                    " order by lname, fname";

    String query3 = "select points " +
       "from scores " +
       "where term = '" +  term_in + "' and " +
       "lineno = '" + ls + "' and " +
       "sid = ? and " +    // substitute ? by sid
       "compname = ?";  // substitute ? by compname
    double total;
    int scaleA;
    int scaleB;
    int scaleC;
    int scaleD;

    Statement stmt = conn.createStatement (); 
    ResultSet rset0;
    try {
      rset0 = stmt.executeQuery(query0);
    } catch (SQLException e) {
        System.out.println("Problem reading scales");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    rset0.next();
    scaleA = rset0.getInt(1);
    scaleB = rset0.getInt(2);
    scaleC = rset0.getInt(3);
    scaleD = rset0.getInt(4);

    System.out.print("SID  LNAME       FNAME     ");

    ResultSet rset1;
    try {
      rset1 = stmt.executeQuery(query1);
    } catch (SQLException e) {
        System.out.println("Problem reading components");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    String comp_names[] = new String[20];
    double comp_maxpoints[] = new double[20];
    double comp_weight[] = new double[20];
    int ncomps=0;
    while (rset1.next()) {
      System.out.print(rset1.getString(1)+" ");
      comp_names[ncomps] = rset1.getString(1);
      comp_maxpoints[ncomps] = rset1.getDouble(2);
      comp_weight[ncomps] = rset1.getDouble(3);
      ncomps++;
    }

    System.out.println("AVG    GRADE");

    ResultSet rset2;
    try {
      rset2 = stmt.executeQuery(query2);
    } catch (SQLException e) {
        System.out.println("Problem reading students");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }

    PreparedStatement stmt2 = conn.prepareStatement(query3);
    while (rset2.next()) {
      total = 0.0;
      System.out.print(rset2.getString(1)+" ");
      System.out.print(rset2.getString(2));
      for (int k=0; k < (12-rset2.getString(2).length()); k++) 
        System.out.print(" ");
      System.out.print(rset2.getString(3));
      for (int k=0; k < (12-rset2.getString(3).length()); k++) 
        System.out.print(" ");
      for (int i=0; i < ncomps; i++) {
        stmt2.setString(1,rset2.getString(1));
        stmt2.setString(2,comp_names[i]);
        ResultSet rset3;
        try {
          rset3 = stmt2.executeQuery();
        } catch (SQLException e) {
            System.out.println("Problem reading scores");
            while (e != null) {
              System.out.println("Message     : " + e.getMessage());
              e = e.getNextException();
            }
            return;
          }
        try {
          rset3.next();
        } catch (SQLException e) {
            System.out.println("No entry in score table for " + 
                               rset2.getString(3) + " in " + comp_names[i]);
            while (e != null) {
              System.out.println("Message     : " + e.getMessage());
              e = e.getNextException();
            }
            continue;
          }
        total = total + 
                 ((rset3.getDouble(1)/comp_maxpoints[i])*comp_weight[i]);
        System.out.print(rset3.getString(1));
      }
      Double tot = new Double(total);
      for (int k2=0; k2 < (6-tot.toString().length()); k2++)
        System.out.print(" ");
      System.out.print(total + "      ");
      if (total >= scaleA) 
        System.out.println("A");
      else if (total >= scaleB) 
        System.out.println("B");
      else if (total >= scaleC) 
        System.out.println("C");
      else if (total >= scaleD) 
        System.out.println("D");
      else
        System.out.println("F");
   } 
   stmt.close();
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


