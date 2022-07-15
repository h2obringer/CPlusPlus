/****************************************************************/
/* Processing Multiple ResultSets (Example 5.5.3)               */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import oracle.jdbc.driver.*;
import java.sql.*; 
import java.io.*; 

class multiple { 
// Note: This class is called call2 in the book
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

    String cnum = readEntry("Enter the customer number: ");


/*
Oracle REFCURSOR Type

The Oracle JDBC driver supports bind variables of type REFCURSOR. 
A REFCURSOR is represented by a JDBC ResultSet. 
Use the getCursor method of the CallableStatement to convert a 
REFCURSOR value returned by a PL/SQL procedure/function. 

Importing classes from the oracle.jdbc.driver package makes 
programs more readable. Here is a simple example. 
The samples subdirectory of the distribution has additional examples.  
*/

   CallableStatement cstmt;
   ResultSet rset;
    
   // Use a PL/SQL block to open the cursors
   cstmt = conn.prepareCall
  ("begin " +
   "open ? for select count(*) from orders where cno = ?;" +
   "open ? for select ono,received from orders where cno = ?;" +
   "open ? for select orders.ono,parts.pno,pname,qty " +
              "from orders,odetails,parts where " +
              "orders.ono = odetails.ono and odetails.pno = parts.pno " +
              "and cno = ?;" +  
   "end;");                                      

   cstmt.setString(2,cnum);
   cstmt.setString(4,cnum);
   cstmt.setString(6,cnum);
   cstmt.registerOutParameter (1, OracleTypes.CURSOR);
   cstmt.registerOutParameter (3, OracleTypes.CURSOR);
   cstmt.registerOutParameter (5, OracleTypes.CURSOR);
   cstmt.execute ();

   rset = ((OracleCallableStatement)cstmt).getCursor(1);
   while (rset.next ()) {
     System.out.println ("Customer has " + rset.getString(1) + " orders");  
   }
   System.out.println("The orders are:");
   rset = ((OracleCallableStatement)cstmt).getCursor(3);
   while (rset.next ()) {
     System.out.print("Order Number " + rset.getString(1));
     System.out.println(":Received on " + rset.getDate(2).toString());
   }
   System.out.println("The order details are:");
   System.out.println("ONO   PNO    PNAME                   QUANTITY");
   rset = ((OracleCallableStatement)cstmt).getCursor(5);
   ResultSetMetaData rsetmd = rset.getMetaData();
   while (rset.next ()) {
     System.out.print(rset.getString(1));
     System.out.print(" " + rset.getString(2));
     System.out.print(" " + rset.getString(3));
     for (int k=0; 
          k<(rsetmd.getColumnDisplaySize(3)-rset.getString(3).length()); k++)
       System.out.print(" ");
     System.out.println(" " + rset.getString(4));
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

