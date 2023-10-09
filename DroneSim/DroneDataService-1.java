package com.dronerecon.ws;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;

/**
 *
 * @author Jasmine Rasmussen
 */
public class DroneDataService extends HttpServlet{


    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("application/json;charset=utf-8");
        response.addHeader("Access-Control-Allow-Origin", "*");

        PrintWriter out = response.getWriter();

        // ##############################
        // 1. Get params passed in.

        // Get the following parameters from the request object and put them into strings:
        // area_id
        // tilex
        // tiley
        // totalcols
        // totalrows
        // r
        // g
        // CHANGE URL IN TRY CATCH STATEMENT (use
        // ALL THE 1s IN URL SHOULD BE YOUR VARIABLES (eg. tilex, tile y, r, g) AND THE URL CONCATENATED.
        // THERE SHOULD BE NO 1s
        // ##############################
        String sAreaID = request.getParameter("area_id");
        String sTileX = request.getParameter("tilex");
        String sTileY = request.getParameter("tiley");
        String sTotalCols = request.getParameter("totalcols");
        String sTotalRows = request.getParameter("totalrows");
        String sR = request.getParameter("r");
        String sG = request.getParameter("g");

        try {

            URL url = new URL("http://127.0.0.1:8080/dronereconportal/PortalDBService?area_id=" + sAreaID +
                    "&tilex=" + sTileX + "&tiley=" + sTileY + "&r=" + sR + "&g=" + sG);
            BufferedReader br = new BufferedReader(new InputStreamReader(url.openStream()));

        } catch (Exception ex) {
            ex.printStackTrace();
        }

        // ##############################
        // 2. Default value of beginning direction.

        // Set a string called sDirection to "right".
        // ##############################
        String sDirection = "right";


        // ##############################
        // 3. Calculate next drone move.

        // Determine next tile to move to.
        // Base this on current x and y.
        // Change sDirection if necessary.
        // Drone must serpentine from top left of grid back and forth down.
        // If rows are done, change sDirection to "stop".
        // ##############################

        // Converts string variables into ints
        int iTileX = Integer.parseInt(sTileX);
        int iTileY = Integer.parseInt(sTileY);
        int iTotalRows = Integer.parseInt(sTotalRows);
        int iTotalCols = Integer.parseInt(sTotalCols);

        // Xs are cols
        // Ys are rows
        // If current y mod 2 equals 0
        if(iTileY % 2 == 0){

            // If the current x is equal to total cols - 1
            if(iTileX == iTotalCols - 1) {

                // Increase next Y by 1
                iTileY++;
                // Set sDiretion to left
                sDirection = "left";
            }
            else{

                // Increase current X by 1
                iTileX++;
            }
        }
        // If current row is odd...
        else {

            // If the current x is equal to 0
            if (iTileX == 0) {
                // Increase next Y by 1
                iTileY++;
                // Set sDirection to right
                sDirection = "right";
            }
            else{

                // Decrease current X by 1
                iTileX--;
                sDirection = "left";
            }
        }

        // Check if we should stop drone
        // If current y equals total rows...
        if(iTileY == iTotalRows) {

            // Set drone to stop
            sDirection = "stop";
        }


        // ##############################
        // 4. Format & Return JSON string to caller.

        /* Return via out.println() a JSON string like this:
        {"area_id":"[area id from above]", "nextTileX":"[next tile x]", "nextTileY":"[next tile y]", "direction":"[direction string from above]"}
        */
        // ##############################

        String sReturnJson = "{\"area_id\":\"" + sAreaID + "\", \"nextTileX\":\"" + iTileX + "\", \"nextTileY\":\""
                + iTileY + "\", \"direction\":\"" + sDirection + "\"}";
        out.println(sReturnJson);

    }
}

