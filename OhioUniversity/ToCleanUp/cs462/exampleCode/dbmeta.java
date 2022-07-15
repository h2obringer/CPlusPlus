import java.sql.*; 
import java.io.*; 

class dbmeta { 
// Note: This class is called meta2 in the book
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
    Connection conn = DriverManager.getConnection(
      "jdbc:oracle:oci7:"+user+"/"+pass);

    DatabaseMetaData dmd = conn.getMetaData();

    System.out.println("Database Product Name = " + 
           dmd.getDatabaseProductName());
    System.out.println("JDBC Driver Name = " + 
           dmd.getDriverName());
    System.out.println("Tables starting with C in schema BOOK are:");
    ResultSet rset = dmd.getTables(null,"BOOK","C%",null); 
    while (rset.next()) {
      System.out.println(rset.getString(3)); // print table name
    }
    int n = dmd.getMaxColumnsInTable();
    System.out.println("Maximum number of columns allowed in a table = " + n);

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

