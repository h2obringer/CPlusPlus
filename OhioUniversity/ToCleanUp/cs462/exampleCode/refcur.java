/****************************************************************/
/* Oracle REFCURSOR processing (Example 5.5.2)                  */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*;
import java.io.*;
import oracle.jdbc.driver.*;

class refcur {
  public static void main (String args [])
       throws SQLException, ClassNotFoundException {

    try {
      Class.forName ("oracle.jdbc.driver.OracleDriver");
    } catch (ClassNotFoundException e) {
        System.out.println ("Could not load the driver"); 
      }

    String user, pass;
    user = readEntry("userid  : ");
    pass = readEntry("password: ");
    Connection conn = DriverManager.getConnection
                      ("jdbc:oracle:oci7:"+user+"/"+pass);

    String term_in = readEntry("Enter Term: ");

    CallableStatement cstmt =
      conn.prepareCall ("{ ? = call refcursor_jdbc.get_courses (?)}");

    cstmt.registerOutParameter (1, OracleTypes.CURSOR);
    cstmt.setString (2, term_in);
    cstmt.execute ();
    ResultSet rset = (ResultSet)cstmt.getObject (1);
    System.out.println("Courses offered during " + term_in + " are:");
    while (rset.next ()) {
      System.out.print(rset.getString(1) + "  ");
      System.out.print(rset.getString(2) + "  ");
      System.out.println(rset.getString(3));
    }
    cstmt.close();
    conn.close();
  }

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

