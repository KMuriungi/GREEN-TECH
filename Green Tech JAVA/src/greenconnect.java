/**
 *@author Hezzy
 */
import java.sql.*;
import javax.swing.*;
/*import
import
import
 import*/
        
        
public class greenconnect 
{
    Connection conn=null;
    public static Connection ConnectGreen()
    {       //method for the connection
    try{
    Class.forName("org.sqlite.JDBC");
    Connection conn =DriverManager.getConnection("jdbc:sqlite:C:\\Users\\MURIUNGI\\Documents\\NetBeansProjects\\Greentech\\Greentech.sqlite");
    
    /*Class.forName("com.mysql.jdbc.Driver");
          Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/jamcham","root", "13252");
          //("jdbc:sqlite:C:\\Users\\ESBORN\\Documents\\NetBeansProjects\\Jamchama\\jamiiDB.sqlite");
             JOptionPane.showMessageDialog(null, "Connection Established"); //The dialog box show when the connection is established
                  return conn;
    */
    JOptionPane.showMessageDialog(null, "Welcome to Green-Tech");
    return conn;
        } 
          catch (Exception e)
        {
            JOptionPane.showMessageDialog(null, e);
            return null;
        }
    
    }
    
}
