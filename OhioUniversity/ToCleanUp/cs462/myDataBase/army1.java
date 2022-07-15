/****************************************************************/
/* GradeBook Application: grade1.java (Section 5.6)             */
/* Needs grade2.java to be compiled                             */
/* Chapter 5; Oracle Programming -- A Primer                    */
/*            by R. Sunderraman                                 */
/****************************************************************/

import java.sql.*; 
import java.io.*; 

class army1 { 

  
  void print_menu() {
    System.out.println("      ARMY PROGRAM\n");
    System.out.println("(1) Add Soldier");
    System.out.println("(2) Add Equipment");
    System.out.println("(3) Add Mission");
    System.out.println("(4) Drop Soldier");
    System.out.println("(5) Drop Equipment");
    System.out.println("(6) Drop Mission");
    System.out.println("(7) Show Soldiers");
    System.out.println("(8) Show Equipment");
    System.out.println("(9) Show Mission");
    System.out.println("(a) Modify Soldier");
    System.out.println("(b) Modify Equipment");
    System.out.println("(c) Modify Mission");
    System.out.println("(d) Show Cost of Equipment per Soldier Report");
    System.out.println("(e) Show Mission Report");
    System.out.println("(q) Quit\n");
  }

  void show_soldiers(Connection conn)
    throws SQLException, IOException {
    
    Statement stmt = conn.createStatement();

    ResultSet rset = stmt.executeQuery 
        ("select * from Soldier");
    while (rset.next ()) { 
      System.out.println(rset.getString(1) + "  " + 
                         rset.getString(2) + "  " +
                         rset.getString(3) + "  " +
                         rset.getString(4) + "  " +
                         rset.getString(5) + "  " +
                         rset.getInt(6) + "  " +
                         rset.getInt(7) + "  " +
                         rset.getString(8) + "  " +
                         rset.getDate(9) + "  " +
                         rset.getString(10) + "  " +
                         rset.getDate(11) + "  " +
                         rset.getString(12) + "  " +
                         rset.getString(13));
    }
  }

  void show_equipment(Connection conn)
    throws SQLException, IOException {
    
    Statement stmt = conn.createStatement();

    ResultSet rset = stmt.executeQuery 
        ("select * from Equipment");
    while (rset.next ()) { 
      System.out.println(rset.getString(1) + "  " +
                         rset.getInt(2) + "  " +
                         rset.getString(3));
    }
  }

  void show_missions(Connection conn)
    throws SQLException, IOException {
    
    Statement stmt = conn.createStatement();

    ResultSet rset = stmt.executeQuery 
        ("select * from Mission");
    while (rset.next ()) { 
      System.out.println(rset.getString(1) + "  " + 
                         rset.getString(2) + "  " +
                         rset.getString(3) + "  " +
                         rset.getString(4) + "  " +
                         rset.getDate(5) + "  " + 
                         rset.getDate(6) + "  " +
                         rset.getInt(7) + "  " +
                         rset.getInt(8));
    }
  }

  void add_soldier(Connection conn) 
    throws SQLException, IOException {
         
    Statement stmt = conn.createStatement(); 

    String SS_Num   = readEntry("Social Security # : ");
    String Fname = readEntry("First Name : ");
    String Mname = readEntry("Middle Name : ");
    String Lname = readEntry("Last Name : ");
    String Sex = readEntry("Sex : ");
    String height = readEntry("Height : ");
    String weight = readEntry("Weight : ");
    String ranking = readEntry("Rank : ");
    String Birth_Date = readEntry("Birth Date : ");
    String Status = readEntry("Status : ");
    String Enlistment_Date = readEntry("Enlistment Date : ");
    String Home_Address = readEntry("Home Address : ");
    String MOS = readEntry("MOS : ");
    String query = "insert into Soldier values (" +
            "'" + Fname + "','" + Mname + "','" 
            + "','" + Lname + "','" + SS_Num + "','" + Sex + "'," + height + "," + 
            weight + ",'" + ranking + "','" + Birth_Date + "','" + 
            Status + "','" + Enlistment_Date + "','" + Home_Address
            + "','" + MOS + "')";
    try {
      int nrows = stmt.executeUpdate(query);
    } catch (SQLException e) {
        System.out.println("Error Adding Soldier Entry");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    stmt.close();
    System.out.println("Added Soldier Entry");
  }

  void add_equipment(Connection conn) 
        throws SQLException, IOException {

    String Ename = readEntry("Equipment Name : ");
    String Cost      = readEntry("Equipment Cost : ");
    String Etype    = readEntry("Equipment Type : ");

    String query = "insert into Equipment values (" +
            "'" + Ename + "'," + Cost + ",'" + 
            Etype + "')";
           
    Statement stmt = conn.createStatement (); 
    try {
      stmt.executeUpdate(query);
    } catch (SQLException e) {
      System.out.println("Equipment was not added!");
      return;
    }
    System.out.println("Equipment was added!");
    stmt.close();
  }

  void add_mission(Connection conn)
    throws SQLException, IOException {

    String CodeName = readEntry("Code Name : ");
    String Mtype = readEntry("Mission Type : ");
    String Start_Date = readEntry("Start Date : ");
    String End_Date = readEntry("End Date : ");
    String Start_Time = readEntry("Start Time : ");
    String End_Time = readEntry("End Time : ");
    String Num_Casualties = readEntry("# of Casualties : ");
    String Percent_collateral_damage = readEntry("% Collateral Damage : ");

    String query = "insert into Mission values (" +
            "'" + CodeName + "','" + Mtype + "','" + 
            Start_Time + "','" + End_Time + "','" + Start_Date
            + "','" + End_Date + "'," + Num_Casualties + "," + Percent_collateral_damage +
            ")";
           
    Statement stmt = conn.createStatement (); 
    try {
      stmt.executeUpdate(query);
    } catch (SQLException e) {
      System.out.println("Equipment was not added!");
      return;
    }
    System.out.println("Equipment was added!");
    stmt.close();
  }

 void modify_soldier(Connection conn) 
      throws SQLException, IOException {

    String SS_Num    = readEntry("Soldier's Social Security Number  : ");
    System.out.println("Select a field to change. Choices are: ");
    System.out.println("Fname, Mname, Lname, Sex, height, weight, ranking,");
    System.out.println("Status, Home_Address, MOS");
    String change_what = readEntry("Field to change :");
    
    String query1 = "select " + change_what + " from Soldier where SS_Num = '" + 
             SS_Num + "'"; 

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
      String new_value = readEntry("Enter New " + change_what + ": ");
      String query2;
      if((change_what == "height" || change_what == "weight")){
        query2 = "update Soldier set " + change_what + " = " + new_value + 
                      " where SS_Num = '" + SS_Num + "'"; 
      }else{
        query2 = "update Soldier set " + change_what + " = '" + new_value +
                      "' where SS_Num = '" + SS_Num + "'";
      }

      try {
        stmt.executeUpdate(query2);
      } catch (SQLException e) {
          System.out.println("Could not modify "+ change_what);
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
          return;
        }
      System.out.println("Modified " + change_what + " successfully");
    }
    else 
      System.out.println(change_what + " not found");
    stmt.close();
  }

  void modify_equipment(Connection conn) 
      throws SQLException, IOException {

    String Ename    = readEntry("Equipment Name  : ");
    System.out.println("Select a field to change. Choices are: ");
    System.out.println("Cost, Etype");
    String change_what = readEntry("Field to change :");
    
    String query1 = "select " + change_what + " from Equipment where Ename = '" + 
             Ename + "'"; 
    
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
      String new_value = readEntry("Enter New " + change_what + ": ");

      String query2;
      if(change_what == "Cost"){
        query2 = "update Equipment set " + change_what + " = " + new_value + 
                      " where Ename = '" + Ename + "'"; 
      }else{
        query2 = "update Equipment set " + change_what + " = '" + new_value + 
                      "' where Ename = '" + Ename + "'";
      }

      try {
        stmt.executeUpdate(query2);
      } catch (SQLException e) {
          System.out.println("Could not modify "+ change_what);
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
          return;
        }
      System.out.println("Modified " + change_what + " successfully");
    }
    else 
      System.out.println(change_what + " not found");
    stmt.close();
  }

  void modify_mission(Connection conn) 
      throws SQLException, IOException {

    String Code_Name    = readEntry("Code Name  : ");
    System.out.println("Select a field to change. Choices are: ");
    System.out.println("Mtype, Start_Time, End_Time, Num_Casualties, Percent_collateral_damage");
    String change_what = readEntry("Field to change :");
    
    String query1 = "select " + change_what + " from Mission where Code_Name = '" + 
             Code_Name + "'"; 

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
      String new_value = readEntry("Enter New " + change_what + ": ");
      String query2;
      if(change_what == "Mtype"){
        query2 = "update Mission set " + change_what + " = " + new_value + 
                      " where Code_Name = '" + Code_Name + "'"; 
      }else{
        query2 = "update Mission set " + change_what + " = '" + new_value + 
                      "' where Code_Name = '" + Code_Name + "'";
      }

      try {
        stmt.executeUpdate(query2);
      } catch (SQLException e) {
          System.out.println("Could not modify "+ change_what);
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
          return;
        }
      System.out.println("Modified " + change_what + " successfully");
    }
    else 
      System.out.println(change_what + " not found");
    stmt.close();
  }

  void drop_soldier(Connection conn) 
      throws SQLException, IOException {
    
    String SS_Num = readEntry("Soldier Social Security Number to drop: ");

    String query0 = "delete Soldier where SS_Num = '" + SS_Num + "'";
    String query1 = "delete Issued where SS_Num = '" + SS_Num + "'";
    String query2 = "delete Execute where SS_Num = '" + SS_Num + "'";

    conn.setAutoCommit(false);
    Statement stmt = conn.createStatement (); 
    int nrows;
    try {
      nrows = stmt.executeUpdate(query1);
      nrows = stmt.executeUpdate(query2);
      nrows = stmt.executeUpdate(query0);
    } catch (SQLException e) {
        System.out.println("Could not drop Soldier");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        conn.rollback();
        return;
      }
    System.out.println("Dropped Soldier");
    conn.commit();
    conn.setAutoCommit(true);
    stmt.close();
  }

  void drop_mission(Connection conn) 
      throws SQLException, IOException {
    
    String Code_Name = readEntry("Code Name to drop: "); 

    String query0 = "delete Mission where Code_Name = '" + Code_Name + "'";
    String query1 = "delete Found_Intel where Code_Name = '" + Code_Name + "'";
    String query2 = "delete Execute where Code_Name = '" + Code_Name + "'";

    conn.setAutoCommit(false);
    Statement stmt = conn.createStatement (); 
    int nrows;
    try {
      nrows = stmt.executeUpdate(query1);
      nrows = stmt.executeUpdate(query2);
      nrows = stmt.executeUpdate(query0);
    } catch (SQLException e) {
        System.out.println("Could not drop Mission");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        conn.rollback();
        return;
      }
    System.out.println("Dropped Mission");
    conn.commit();
    conn.setAutoCommit(true);
    stmt.close();
  }

  void drop_equipment(Connection conn) 
      throws SQLException, IOException {
    
    String Ename = readEntry("Equipment Name to drop: "); 

    String query0 = "delete Equipment where Ename = '" + Ename + "'";
    String query1 = "delete Issued where Ename = '" + Ename + "'";

    conn.setAutoCommit(false);
    Statement stmt = conn.createStatement (); 
    int nrows;
    try {
      nrows = stmt.executeUpdate(query1);
      nrows = stmt.executeUpdate(query0);
    } catch (SQLException e) {
        System.out.println("Could not drop Equipment");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        conn.rollback();
        return;
      }
    System.out.println("Dropped Equipment");
    conn.commit();
    conn.setAutoCommit(true);
    stmt.close();
  }


  void print_cost_per_Soldier(Connection conn) 
        throws SQLException, IOException {

    String query0 = "select SS_Num,Fname,Mname,Lname " +
                     "from Soldier";
    String query1;
    Statement stmt = conn.createStatement (); 
    Statement stmt2 = conn.createStatement ();
    ResultSet rset0;

    try {
      rset0 = stmt.executeQuery(query0);
    } catch (SQLException e) {
        System.out.println("Problem reading Soldiers");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    String SS_Num;
    String FirstName;
    String MiddleName;
    String LastName;
    ResultSet rset1;
    double totalCost;
    double overallCost=0.0;
    double totalSoldiers=0.0;
    double minCost=99999999; //pick large value
    double maxCost=0.0; //pick lowest value

    System.out.println("\n        Total Money Spent on Equipment per Soldier         ");
    System.out.println("FNAME\t\tMNAME\t\tLNAME\t\t\tTotal Equipment Cost");
    System.out.println("-----\t\t-----\t\t-----\t\t\t--------------------");
    while(rset0.next()){
      SS_Num=rset0.getString(1);
      FirstName=rset0.getString(2);
      MiddleName=rset0.getString(3);
      LastName=rset0.getString(4);
      query1 = "select Cost " + 
               "from Equipment,Issued " + 
               "where Equipment.Ename = Issued.Ename " +
               "and Issued.SS_Num = '" + SS_Num + "'";
      try {
        rset1 = stmt2.executeQuery(query1);
      } catch (SQLException e) {
          System.out.println("Problem reading Costs");
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
          return;
        }
      totalCost=0.0;
      while(rset1.next()){
        try{
          totalCost+=rset1.getDouble(1);
        } catch (SQLException e) {
            while(e != null){
              e=e.getNextException();
            }
            continue;
          }
      }
      if(minCost>totalCost){
        minCost=totalCost;
      }
      if(maxCost<totalCost){
        maxCost=totalCost;
      }
      overallCost+=totalCost;
      ++totalSoldiers;
      System.out.println(FirstName + "\t\t" + MiddleName + "\t\t" + LastName + "\t\t\t" + 
                         totalCost);
      
    }
    System.out.println("\nAmount of Soldiers =\t\t\t\t" + totalSoldiers);
    System.out.println("Min Cost on Equipment for a Soldier =\t\t" + minCost);
    System.out.println("Max Cost on Equipment for a Soldier =\t\t" + maxCost);
    System.out.println("Average Cost for Equipment per Soldier =\t" + overallCost/totalSoldiers);
    System.out.println("");
    stmt.close();
  }

  void print_mission_report(Connection conn) 
        throws SQLException, IOException {

    String query0 = "select Code_Name,Mtype,Num_Casualties,Percent_collateral_damage " + 
               "from Mission";
    String query1;
    //String query2 = "select unique Mtype " + 
                    //"from Mission";
    //String query3;
    
    Statement stmt = conn.createStatement (); 
    Statement stmt2 = conn.createStatement ();
    Statement stmt3 = conn.createStatement ();
    ResultSet rset0;

    try {
      rset0 = stmt.executeQuery(query0);
    } catch (SQLException e) {
        System.out.println("Problem reading Soldiers");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
        return;
      }
    String Code_Name;
    String Mtype;
    int Num_Casualties;
    int Percent_collateral_damage;
    ResultSet rset1;
    String Fname;
    String Lname;
    //double totalCost;
    //double overallCost=0.0;
    //double totalSoldiers=0.0;
    //double minCost=99999999; //pick large value
    //double maxCost=0.0; //pick lowest value

    System.out.println("\n        Mission Report         ");
    System.out.println("Code Name\tMission Type\t# of Casualties\t% Collateral Damage");
    System.out.println("---------\t------------\t---------------\t-------------------");
    while(rset0.next()){
      Code_Name=rset0.getString(1);
      Mtype=rset0.getString(2);
      Num_Casualties=rset0.getInt(3);
      Percent_collateral_damage=rset0.getInt(4);
      System.out.println(Code_Name + "\t" + Mtype + "\t\t" + Num_Casualties + "\t\t" + Percent_collateral_damage);
      query1 = "select Fname,Lname " +
               "from Soldier,Execute " +
               "where Soldier.SS_Num = Execute.SS_Num " + 
               "and Code_Name = '" + Code_Name + "'";
      try {
        rset1 = stmt2.executeQuery(query1);
      } catch (SQLException e) {
          System.out.println("Problem reading Soldier to Mission relationship");
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
          return;
        }
      System.out.println("\t\tSoldiers Involved: ");
      while(rset1.next()){
        try{
          Fname=rset1.getString(1);
          Lname=rset1.getString(2);
          System.out.println("\t\t" + Fname + " " + Lname);
        } catch (SQLException e) {
            while(e != null){
              e=e.getNextException();
            }
            continue;
          }
      }
      System.out.println("");
    /***********************************************************************/
 
    }

    /*try {
      rset2 = stmt.executeQuery(query2);
    } catch (SQLException e) {
        System.out.println("Problem reading Mission");
        while (e != null) {
          System.out.println("Message     : " + e.getMessage());
          e = e.getNextException();
        }
      return;
      String MissionType;
      double minCasualties=99999999;
      double maxCasualties=0.0;
      double totalCas=0.0;
      double minCD=99999999;
      double maxCD=0.0;
      double totalCD=0.0;
      double totalMissions=0.0;
      
      while(rset2.next()){
        MissionType=rset2.getString(1);
        query3="select Num_Casualties,Percent_collateral_damage " +
               "from Mission " + 
               "where Mtype = '" + MissionType + "'";
      try {
        rset3 = stmt2.executeQuery(query3);
      } catch (SQLException e) {
          System.out.println("Problem reading Mission part2");
          while (e != null) {
            System.out.println("Message     : " + e.getMessage());
            e = e.getNextException();
          }
          return;
        }
      totalMissions=0.0;
      while(rset3.next()){
        try{
          totalCost+=rset3.getDouble(1);
        } catch (SQLException e) {
            while(e != null){
              e=e.getNextException();
            }
            continue;
          }
      }
    }*/
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

