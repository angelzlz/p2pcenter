<%mnr_debug = 0%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">

<title>���Ӽ��</title>

<style type="text/css">
body,td {
 font-family: "Verdana,Arial";
 font-size: 12px;
 color: #cccccc;
 margin: 0;
 padding: 0;
 SCROLLBAR-ARROW-COLOR: #2a7f01; SCROLLBAR-DARKSHADOW-COLOR: #def3f3; SCROLLBAR-BASE-COLOR: #efefef
}
</style>

</head>

<body bgcolor="#000000">
<div align="right">
  <table width="100%" border="0">
    <tr> 
      <td>
<span id="text"></span>
      </td>
    </tr>
  </table>
</div>


<script id="scr" language=javascript src="http://localhost:<%=Request("Port")%>/monitor.js?channelhash=<%=Request("channelhash")%>&monitor=1"></script>

<script language="javascript">
  var timeid = null;
  var use_time = 1;
  function loadscr() {
       clearTimeout(timeid);
 scr.src = "http://localhost:<%=Request("Port")%>/monitor.js?channelhash=<%=Request("channelhash")%>&monitor=" + timeid;
 text.innerHTML = "��Ŀ��" + mnr_channelname + "<br>";
 text.innerHTML += "���ߣ�" + mnr_id.length + " ��<br>";
 for ( var ic = 0; ic < mnr_id.length; ic ++)
 {
  text.innerHTML += ("-------------------------------<br>");
  text.innerHTML += ("�û�ID:" + mnr_id[ic] + "<br>");
  text.innerHTML += ("������ַ:" + mnr_externalip[ic] + ":" + mnr_externaludpport[ic] + "<br>");
  var speed = mnr_recvbytes[ic] / 10000;
  text.innerHTML += ("�����ٶ�:" + speed.toFixed(2) + " KB/S<br>");

  var downkbs = (mnr_receiveblocks[ic] * 933 / 1024);
  if ( downkbs > 1024)
  {
    downkbs /= 1024;
    text.innerHTML += ("��������:" + downkbs.toFixed(2) + " MB<br>");
  }
  else
  {
    text.innerHTML += ("��������:" + downkbs.toFixed(2) + " KB<br>");
  }

  var speed = mnr_uploadbytes[ic] / 10000;
  text.innerHTML += ("�ϴ��ٶ�:" + speed.toFixed(2) + " KB/S<br>");

<%If mnr_debug = 1 Then%>

  var upkbs = (mnr_sendblocks[ic] * 933 / 1024);
  if ( upkbs > 1024)
  {
    upkbs /= 1024;
    text.innerHTML += ("�ϴ�����:" + upkbs.toFixed(2) + " MB<br>");
  }
  else
  {
    text.innerHTML += ("�ϴ�����:" + upkbs.toFixed(2) + " KB<br>");
  }

  text.innerHTML += ("����TCP�˿�:" + mnr_externaltcpport[ic] + "<br>");
  text.innerHTML += ("�������:" + mnr_requestblocks[ic] + "<br>");
  text.innerHTML += ("�յ�����:" + mnr_receiveblocks[ic] + "<br>");
  text.innerHTML += ("���������:" + mnr_getblocks[ic] + "<br>");
  text.innerHTML += ("���Ϳ���:" + mnr_sendblocks[ic] + "<br>");
  text.innerHTML += ("���ս�����:" + mnr_healthrate[ic] + "%<br>");
  text.innerHTML += ("���ͽ�����:" + mnr_returnrate[ic] + "%<br>");
  text.innerHTML += ("�Ƿ�ΪԴ:" + mnr_issource[ic] + "<br>");
<%End If%>
 }
 use_time ++;
 timeid = setTimeout("loadscr();", 1000);
}
loadscr();
window.focus();
</script>

</body>
</html>


