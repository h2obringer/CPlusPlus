import java.sql.*; 
import java.io.*; 

public class browse { 
  public static void main (String args []) 
      throws SQLException, IOException { 

    try {
      Class.forName ("oracle.jdbc.driver.OracleDriver");
    } catch (ClassNotFoundException e) {
        System.out.println ("Could not load the driver"); 
      }

    String user, pass;
    user = "book"; //readEntry("userid  : ");
    pass = "book"; //readEntry("password: ");
    Connection conn = DriverManager.getConnection
                ("jdbc:oracle:thin:@tinman.cs.gsu.edu:1521:sid9ir2",
                 user,pass);

    Statement stmt = conn.createStatement(
        ResultSet.TYPE_SCROLL_INSENSITIVE,
        ResultSet.CONCUR_READ_ONLY );

    ResultSet rset = stmt.executeQuery 
        ("select isbn,author from books where title like '%w%'");

    rset.last();
    int nRows = rset.getRow();
    System.out.println("Number of rows in the result set is " +
      nRows);

    int currentRow = 1;
    while (currentRow==currentRow) {
      rset.absolute(currentRow);
      int n = 0;
      System.out.println("");
      for (int i=currentRow; i<=nRows; i++) {
        if (n == 5)
          break;
        System.out.println(rset.getString(1)+" "+rset.getString(2));
        rset.next();
        n++;
      }
      if (currentRow == (((nRows/5)*5)+1)) {
        String opt = readEntry("\n          p: previous 5, q: quit");
        if (opt.equals("q"))
          return;
        else if (opt.equals("p"))
          currentRow -= 5;
      }
      else if (currentRow == 1) {
        String opt = readEntry("\n          n: next 5, q: quit");
        if (opt.equals("q"))
          return;
        else if (opt.equals("n"))
          currentRow += 5;
      }
      else {
        String opt = readEntry("\n          n: next 5, p: previous 5, q: quit");
        if (opt.equals("q"))
          return;
        else if (opt.equals("n"))
          currentRow += 5;
        else if (opt.equals("p"))
          currentRow -= 5;
      }
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

