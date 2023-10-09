<%@ page import="com.dronerecon.ws.AreaGridTile" %>
<%@ page import="com.dronerecon.ws.DBManager" %>
<%@ page import="java.util.ArrayList" %>

<html>
	<body>
	
	<table style = "margin-left:auto;margin-right:auto;">
		<tr>
			<td colspan="100%" style="text-align:center; background-color:BAC99B">
				<p>Area ID:</p>
			</td>
				<%
				// Sets area id
				String sAreaID = request.getParameter("area_id");
				%>
		</tr>
				<%
				// This instantiates DBManager
				DBManager oDBManager = new DBManager();
				oDBManager.DBLocation = System.getProperty("catalina.base") + "\\webapps\\dronereconportal\\db\\" + oDBManager.DBLocation;
				
				// Creates a new ArrayList and stores readAreaGridTiles in the new list
				ArrayList <AreaGridTile> alValues = new ArrayList<AreaGridTile>(oDBManager.readAreaGridTiles(sAreaID));
			
				
				// Variables to hold max red/green values and their x,y coordinates
				int iMaxRed = 0;
				int iMaxGreen = 0;
				int iRValue;
				int iGValue;
				
				int iXMaxRed = 0;
				int iYMaxRed = 0;
				int iXMaxGreen = 0;
				int iYMaxGreen = 0;
				
				// For loop checks for x,y green with highest red and x,y tile with highest green
				for (int x = 0; x < alValues.size(); x++){
					
					// To get red value from ArrayList
					iRValue = (Integer)alValues.get(x).r;
					// To get green value from ArrayList
					iGValue = (Integer)alValues.get(x).g;
					
					// If the current record's R value is higher, stores in iMaxRed
					if(iRValue > iMaxRed){
						iMaxRed = iRValue;
						
						// Stores the X,Y coordinates of the record
						iXMaxRed = (Integer)alValues.get(x).x;
						iYMaxRed = (Integer)alValues.get(x).y;
						
					}
					
					// If the current record's G value is higher, stores in iMaxGreen
					if(iGValue > iMaxGreen){
						iMaxGreen = iGValue;
						
						// Stores the X,Y coordinates of the record
						iXMaxGreen = (Integer)alValues.get(x).x;
						iYMaxGreen = (Integer)alValues.get(x).y;
					}				
				}
				%>
				
		<tr>		
			<td>
				<%
				out.println("The coordinates for the highest Red value are: X:" + iXMaxRed + ", Y:" + iYMaxRed);
				%>
			</td>
		</tr>
		<tr>
				<td>
				<%
				out.println("The coordinates for the highest Green value are: X:" + iXMaxGreen + ", Y:" + iYMaxGreen);
				%>
			</td>
		</tr>
	</table>
	
	</body>
</html>