/****************************************************************/
/* JDBC Example -- Create Table (Example 5.4.2)                 */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/
import java.sql.*; 
import java.io.*; 

class create_table { 

  public static void main(String args[]) throws SQLException, IOException {

    String query;
    query =  "create table deleted_scores (" +
             "sid       varchar2(5) not null," +
             "term      varchar2(10) not null," +
             "lineno    number(4) not null," +
             "compname  varchar2(15) not null," +
             "points    number(4) check(points >= 0))";
           
    try {
      Class.forName ("oracle.jdbc.driver.OracleDriver");
    } catch (ClassNotFoundException e) {
        System.out.println("Could not load driver");
      }

    String user, pass;
    user = readEntry("userid  : ");
    pass = readEntry("password: ");
    Connection conn = DriverManager.getConnection
                      ("jdbc:oracle:oci7:"+user+"/"+pass);

    Statement stmt = conn.createStatement (); 
    try {
      stmt.executeUpdate(query);
    } catch (SQLException e) {
      System.out.println("Could not create table");
      return;
    }
    System.out.println("Table created");

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

