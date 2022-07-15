/****************************************************************/
/* CallableStatement Example -- (Example 5.4.5)                 */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class call1 { 
// Note: This class is called call3 in the book
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

    int enum = readNumber("Enter the employee number: ");
    int cnum = readNumber("Enter the customer number: ");
    int onum = readNumber("Enter the order    number: ");
    CallableStatement stmt = conn.prepareCall 
      ("{call process_orders.add_order(?,?,?,?)}"); 
    stmt.setInt(1,onum);
    stmt.setInt(2,cnum);
    stmt.setInt(3,enum);
    stmt.setNull(4,Types.DATE);
    conn.setAutoCommit(false);
    try {
      stmt.executeUpdate(); 
    } catch (SQLException e) {
        System.out.println("Could not add order");
        conn.rollback();
        return;
      }
    stmt = conn.prepareCall 
      ("{call process_orders.add_order_details(?,?,?)}"); 
    do {
      int pnum = readNumber("Enter the part number (0 to stop): ");
      if (pnum == 0)
        break;
      int qty = readNumber("Enter the quantity   : "); 
      stmt.setInt(1,onum);
      stmt.setInt(2,pnum);
      stmt.setInt(3,qty);
      try {
        stmt.executeUpdate();
      } catch (SQLException e) {
          System.out.println("Could not add odetail");
        }
    } while (true);
  conn.commit();
  stmt.close();
  conn.close();
  } 

  //readNumber function -- to read input number
  static int readNumber(String prompt) throws IOException {

     String snum;
     int num = 0;
     boolean numok;
     do {
       snum = readEntry(prompt);
       try {
         num = Integer.parseInt(snum);
         numok = true;
       } catch (NumberFormatException e) {
           numok = false;
           System.out.println("Invalid number; enter again");
         }
     } while (!numok);
     return num;
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

