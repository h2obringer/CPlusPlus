/****************************************************************/
/* CallableStatement Example (Example 5.4.6)                    */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class call2 { 
// Note: This class is called call1 in the book
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

    String cnum = readEntry("Enter the customer number to find city: ");
    CallableStatement stmt = conn.prepareCall ("{? = call get_city (?)}"); 
    stmt.setString(2,cnum);
    stmt.registerOutParameter(1,Types.VARCHAR);

    stmt.execute(); 

    String city = stmt.getString(1);
    if (stmt.wasNull())
      System.out.println("Customer's city = Null");
    else
      System.out.println("Customer's city = "+ stmt.getString(1));

    stmt.close();
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

