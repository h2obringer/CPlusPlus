/****************************************************************/
/* A Simple JDBC Program (Section 5.2)                          */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class simple { 
  public static void main (String args []) 
      throws SQLException, IOException { 

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

    Statement stmt = conn.createStatement (); 

    ResultSet rset = stmt.executeQuery 
        ("select distinct eno,ename,zip,hdate from employees");
    while (rset.next ()) { 
      System.out.println(rset.getInt(1) + "  " +
                         rset.getString(2) + "  " +
                         rset.getInt(3) + "  " +
                         rset.getDate(4));
    } 

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

