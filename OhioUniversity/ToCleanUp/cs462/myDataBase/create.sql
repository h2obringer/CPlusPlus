create table Soldier(
  Fname varchar2(12), 
  Mname varchar2(12), 
  Lname varchar2(15), 
  SS_Num char(11) primary key, 
  Sex char(1),				--M or F for male or female
  height integer check (height>57), 	--The minimum height is 58 inches
  weight integer check (weight>90), 	--The minimum weight is 91 Ibs
  ranking char(4),
  Birth_Date date,
  Status char(1),			--A for active and R for reserves
  Enlistment_Date date,
  Home_Address varchar2(50),
  MOS varchar2(45)
);
create table Equipment(
  Ename varchar2(18) primary key,
  Cost number(15,2),
  Etype varchar2(21)
);
create table Mission(
  Code_Name varchar2(13) primary key,
  Mtype varchar2(17),
  Start_Time char(4),
  End_Time char(4),
  Start_Date date,
  End_Date date,
  Num_Casualties integer,
  Percent_collateral_damage integer check (Percent_collateral_damage>=0) check (Percent_collateral_damage<=100)
);
create table Issued(
  Ename varchar2(15),
  SS_Num char(11),
  EID_Num integer,
  Date_Issued date,
  primary key (Ename,SS_Num),
  foreign key (Ename) references Equipment,
  foreign key (SS_Num) references Soldier
);
create table Execute(
  SS_Num char(11),
  Code_Name varchar2(13),
  primary key (SS_Num,Code_Name),
  foreign key (SS_Num) references Soldier,
  foreign key (Code_Name) references Mission
);
create table Found_Intel(
  Code_Name varchar2(13),
  Intel varchar2(50),
  primary key (Code_Name,Intel),
  foreign key (Code_Name) references Mission
);
