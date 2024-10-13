<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:output method="html"/>

  <!-- Шаблон для сортировки по отрасли -->
  <xsl:template match="/successStories">
    <html>
      <body>
        <h2>Таблица успехов нейронных сетей</h2>
        <table border="1">
          <tr>
            <th>Отрасль</th>
            <th>Пример</th>
            <th>Описание</th>
            <th>Изображение</th>
          </tr>
          <xsl:apply-templates select="story">
            <xsl:sort select="industry"/>
          </xsl:apply-templates>
        </table>

        <h2>Подробные описания</h2>
        <xsl:apply-templates select="story" mode="detailed"/>
      </body>
    </html>
  </xsl:template>

  <!-- Шаблон для отображения строк таблицы -->
  <xsl:template match="story">
    <tr>
      <td><xsl:value-of select="industry"/></td>
      <td><xsl:value-of select="example"/></td>
      <td><xsl:value-of select="description"/></td>
      <td>
        <xsl:if test="string-length(image) > 0">
          <img src="{image}" width="100" height="100"/>
        </xsl:if>
      </td>
    </tr>
  </xsl:template>

  <!-- Шаблон для построчного отображения -->
  <xsl:template match="story" mode="detailed">
    <div>
      <h3><xsl:value-of select="industry"/>: <xsl:value-of select="example"/></h3>
      <p><xsl:value-of select="description"/></p>
      <xsl:if test="string-length(image) > 0">
        <img src="{image}" width="200"/>
      </xsl:if>
    </div>
  </xsl:template>

</xsl:stylesheet>
