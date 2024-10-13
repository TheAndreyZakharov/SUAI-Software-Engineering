package servlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet ("/servlet/*")
public class Main extends HttpServlet {
    private List<ItemObj> list = new ArrayList<>();

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();

        if (pathInfo == null || pathInfo.equals("/")) {
            String stock_name = request.getParameter("stockName");
            String stockID = request.getParameter("stockID");

            String purchase_date = request.getParameter("purchaseDate");
            if(!stock_name.equals("") && stockID != null && !stockID.trim().isEmpty() && !purchase_date.equals("")) {
                list.add(new ItemObj(stock_name, stockID, purchase_date));
                response.getWriter().write("Bought");
            } else {
                send_warning(response);
            }
        } else if (pathInfo.equals("/display")) {
            display(request, response);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();

        if (pathInfo == null || pathInfo.equals("/")) {}
        request.setCharacterEncoding("UTF-8");
        String stock_name = request.getParameter("stockName");
        String stockID = request.getParameter("stockID");

        if(!stock_name.equals("") && stockID != null && !stockID.trim().isEmpty()) {
            for (ItemObj item : list) {
                if(item.getStock_name().equals(stock_name) && item.getStockID().equals(stockID)) {
                    list.remove(item);
                    response.getWriter().write("Sold");
                }
            }
        }
    }

    protected void display(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (!list.isEmpty()) {
            response.setContentType("text/html; charset=UTF-8");
            response.getWriter().write("<table style='border-collapse: collapse;'>");
            response.getWriter().write("<tr><th style='width: 20%; border: 1px solid black;'>Название акции</th><th style='width: 20%; " +
                    "border: 1px solid black;'>ID акции</th><th style='width: 20%; border: 1px solid black;'>Дата покупки</th></tr>");
            for (ItemObj item : list) {
                response.getWriter().write(String.format(
                        "<tr><td style='width: 20%%; border: 1px solid black;'>%s</td><td style='width: 20%%; border: 1px solid black;'>%s</td><td style='width: 20%%; border: 1px solid black;'>%s</td></tr>",
                        item.getStock_name(), item.getStockID(), item.getPurchase_date()));
            }
            response.getWriter().write("</table>");
        } else {
            response.getWriter().write("List is empty");
        }
    }

    protected void send_warning(HttpServletResponse response) throws IOException {
        response.getWriter().write("Please enter all values!");
    }
}
