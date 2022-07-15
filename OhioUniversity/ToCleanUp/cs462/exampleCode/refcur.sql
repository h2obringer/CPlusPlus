-----------------------------------------------------------------
-- Oracle REFCURSOR Example (Example 5.5.2)                     -
-- PL/SQL Package refcursor_jdbc                                -
-- Chapter 5; Oracle Programming -- A Primer                    -
--            by R. Sunderraman                                 -
-----------------------------------------------------------------

create or replace package refcursor_jdbc as
  type refcurtype is ref cursor;
  function get_courses (term_in varchar2) return refcurtype;
end refcursor_jdbc;
/
show errors
create or replace package body refcursor_jdbc as
  function get_courses (term_in varchar2) return refcurtype as
    rc refcurtype;
  begin
   open rc for 
     select lineno, courses.cno, ctitle
     from   courses, catalog
     where  courses.cno = catalog.cno and
            courses.term = term_in;
   return rc;
  end;
end refcursor_jdbc;
/
show errors

