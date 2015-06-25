<?php

###################################################################################################

function echoError($errorid, $parameter = '')
{
  echo '
<error>
  <code>'.$errorid.'</code>
  <text>';
  switch ($errorid)
  {
  case 1:
    echo 'Required parameter "username" is not defined';
    break;
  case 2:
    echo 'Required parameter "userid" is not defined';
    break;
  case 3:
    echo 'Required parameter "tabletid" is not defined';
    break;
  case 4:
    echo 'Required parameter "sessionid" is not defined';
    break;
  case 5:
    echo 'Required parameter "gestureid" is not defined';
    break;
  case 6:
    echo 'The username "'.$parameter.'" is already in use by a different user';
    break;
  case 7:
    echo 'Failed to insert the user into the database';
    break;
  case 8:
    echo 'User "'.$parameter.'" not found in the database';
    break;
  case 9:
    echo 'Invalid username or password';
    break;
  case 10:
    echo 'Failed to insert a session into the database';
    break;
  case 11:
    echo 'Session '.$parameter.' not found in the database';
    break;
  case 12:
    echo 'Session of tablet "'.$parameter.'" not found in the database';
    break;
  case 13:
    echo 'Unable to insert session gesture';
    break;
  case 14:
    echo 'Unknown command "'.$parameter.'"';
    break;
  case 15:
    echo 'Required parameter "cmd" is not defined';
    break;
  case 16:
    echo 'Required upload data "photo" is not defined';
    break;
  case 17:
    echo 'Unable to store uploaded data at "'.$parameter.'"';
    break;
  case 18:
    echo 'Required parameter "languageid" is not defined';
    break;
  case 19:
    echo 'Unable to send e-mail to "'.$parameter.'"';
    break;
  case 20:
    echo 'Visualization not triggered, there is already an active visualization';
    break;
  default:
    echo 'Unknown error';
    break;
  }
  echo '</text>
</error>';
}

###################################################################################################

function getLangString($str, $languageid)
{
  global $db;

  $dbresult = pg_query($db, "SELECT string FROM uilangstring
                              WHERE reference = '".pg_escape_string($str)."' AND
                                    languageid = '".$languageid."'");
  if (pg_num_rows($dbresult) > 0)
  {
    $result = pg_fetch_result($dbresult, 0, 'string');
    if ($result != '')
    {
      return $result;
    }
  }
  return $str;
}

###################################################################################################

function getExhibitionState()
{
  global $db;
  $exhibitionstate = pg_fetch_object(pg_query($db, "SELECT * FROM exhibitionstate LIMIT 1"));
  return $exhibitionstate;
}

###################################################################################################

function sendRegistrationMail($userid)
{
  global $db;
  $user = pg_fetch_object(pg_query($db, "SELECT * FROM \"user\" WHERE id = ".$userid));
  if (is_object($user) && $user->isemail)
  {
    $header = "From: \"".getLangString("MAIL_FROM", $user->languageid)."\" <".MAILADDR_FROM.">\r\n";
    $header .= "MIME-Version: 1.0\r\n";
    $header .= "Content-Type: text/plain; charset=\"utf-8\"\r\n";
    $subject = getLangString("MAIL_SUBJECT", $user->languageid);
    $body = getLangString("MAIL_GREETING", $user->languageid);
    if ($user->firstname != '')
    {
      $body .= " ".$user->firstname;
    }
    if ($user->surname != '')
    {
      $body .= " ".$user->surname;
    }
    $body .= "!\r\n\r\n".getLangString("MAIL_SENTENCE1", $user->languageid);
    $body .= "\r\n".getLangString("MAIL_USERNAME", $user->languageid)." \"".$user->username."\"";
    $body .= "\r\n".getLangString("MAIL_PASSWORD", $user->languageid)." \"".$user->password."\"";
    $body .= "\r\n\r\n".getLangString("MAIL_FINAL", $user->languageid);
    if (!mail($user->username, $subject, $body, $header))
    {
      echoError(19, $user->username);
      return false;
    }
  }
  return true;
}

function echoUser($userid)
{
  global $db;
  $user = pg_fetch_object(pg_query($db, "SELECT * FROM \"user\" WHERE id = ".$userid));
  if (is_object($user))
  {
    echo '
<user>
  <id>'.$user->id.'</id>
  <username><![CDATA['.$user->username.']]></username>
  <isemail>'.($user->isemail == "t" ? "1":"0").'</isemail>
  <languageid>'.$user->languageid.'</languageid>';
  if ($user->imagepath != '')
  {
    echo '
  <imagepath><![CDATA['.$user->imagepath.']]></imagepath>
  <imageurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$user->imagepath.']]></imageurl>';
  }
  if ($user->firstname != '')
  {
    echo '
  <firstname><![CDATA['.$user->firstname.']]></firstname>';
  }
  if ($user->surname != '')
  {
    echo '
  <surname><![CDATA['.$user->surname.']]></surname>';
  }
  if ($user->address != '')
  {
    echo '
  <address><![CDATA['.$user->address.']]></address>';
  }
  if ($user->zipcode != '')
  {
    echo '
  <zipcode><![CDATA['.$user->zipcode.']]></zipcode>';
  }
  if ($user->city != '')
  {
    echo '
  <city><![CDATA['.$user->city.']]></city>';
  }
  if ($user->country != '')
  {
    echo '
  <country><![CDATA['.$user->country.']]></country>';
  }
  echo '
  <isdemo>'.($user->isdemo == "t" ? "1":"0").'</isdemo>
</user>';
  }
  else
  {
    echoError(8, $userid);
  }
}

###################################################################################################

function echoSession($sessionid)
{
  global $db;
  $session = pg_fetch_object(pg_query($db, "SELECT * FROM \"usersession\" WHERE id = ".$sessionid));
  if (is_object($session))
  {
    $qrcodefile = QRCODE_PATH.$session->tabletid.".png";
    if (!is_file($qrcodefile))
    {
      shell_exec("qrencode -o \"".$qrcodefile."\" -s 25 \"".$session->tabletid."\"");
    }
    echo '
<session>
  <id>'.$session->id.'</id>
  <tabletid>'.$session->tabletid.'</tabletid>
  <qrcodepath><![CDATA['.substr($qrcodefile, strlen(ROOT_PATH)).']]></qrcodepath>
  <qrcodeurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].substr($qrcodefile, strlen(ROOT_PATH)).']]></qrcodeurl>';
    if ($session->userid > 0)
    {
      echo '
  <userid>'.$session->userid.'</userid>';
    }
    echo '
  <startedat>'.$session->startedat.'</startedat>';
    if ($session->committedat != '')
    {
      echo '
  <committedat>'.$session->committedat.'</committedat>';
    }
    if ($session->sentat != '')
    {
      echo '
  <sentat>'.$session->sentat.'</sentat>';
    }
    if ($session->finishedat != '')
    {
      echo '
  <finishedat>'.$session->finishedat.'</finishedat>';
    }
    echo '
  <languageid>'.$session->languageid.'</languageid>';
    $gestures = pg_query($db, "SELECT sg.gestureid, sg.sequence, sg.collectedat, sg.committed,
                                      g.themeid, g.iconsmallpath, g.co2impact, gt.txt AS name FROM sessiongestures sg
                                 LEFT JOIN usersession s ON s.id = sg.sessionid
                                 LEFT JOIN gesture g ON g.id = sg.gestureid
                                 LEFT JOIN gesturetext gt ON gt.id = sg.gestureid AND
                                                             gt.languageid = s.languageid AND
                                                             gt.contenttype = 'name'
                                WHERE sg.sessionid = ".$session->id."
                                ORDER BY sequence");
    if (pg_num_rows($gestures) > 0)
    {
      echo '
    <gestures>';
      while (is_object($gesture = pg_fetch_object($gestures)))
      {
        echo '
      <gesture>
        <gestureid>'.$gesture->gestureid.'</gestureid>
        <sequence>'.$gesture->sequence.'</sequence>
        <collectedat>'.$gesture->collectedat.'</collectedat>
        <committed>'.($gesture->committed == "t" ? "1":"0").'</committed>
        <themeid>'.$gesture->themeid.'</themeid>
        <iconsmallpath><![CDATA['.$gesture->iconsmallpath.']]></iconsmallpath>
        <iconsmallurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->iconsmallpath.']]></iconsmallurl>
        <co2impact>'.$gesture->co2impact.'</co2impact>
        <name><![CDATA['.$gesture->name.']]></name>
      </gesture>';
      }
      echo '
    </gestures>';
    }
    $messages = pg_query($db, "SELECT sm.gestureid, sm.sequence, sm.collectedat, sm.sent,
                                      g.themeid, g.iconsmallpath, g.co2impact, gt.txt AS name FROM sessionmessages sm
                                 LEFT JOIN usersession s ON s.id = sm.sessionid
                                 LEFT JOIN gesture g ON g.id = sm.gestureid
                                 LEFT JOIN gesturetext gt ON gt.id = sm.gestureid AND
                                                             gt.languageid = s.languageid AND
                                                             gt.contenttype = 'name'
                                WHERE sm.sessionid = ".$session->id."
                                ORDER BY sequence");
    if (pg_num_rows($messages) > 0)
    {
      echo '
    <messages>';
      while (is_object($gesture = pg_fetch_object($messages)))
      {
        echo '
      <gesture>
        <gestureid>'.$gesture->gestureid.'</gestureid>
        <sequence>'.$gesture->sequence.'</sequence>
        <collectedat>'.$gesture->collectedat.'</collectedat>
        <sent>'.($gesture->sent == "t" ? "1":"0").'</sent>
        <themeid>'.$gesture->themeid.'</themeid>
        <iconsmallpath><![CDATA['.$gesture->iconsmallpath.']]></iconsmallpath>
        <iconsmallurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->iconsmallpath.']]></iconsmallurl>
        <co2impact>'.$gesture->co2impact.'</co2impact>
        <name><![CDATA['.$gesture->name.']]></name>
      </gesture>';
      }
      echo '
    </messages>';
    }
    echo '
</session>';
  }
  else
  {
    echoError(11, $sessionid);
  }
}

###################################################################################################

function generateRandomString($length = 10)
{
  $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
  $randomString = '';
  for ($i = 0; $i < $length; $i++) {
    $randomString .= $characters[rand(0, strlen($characters) - 1)];
  }
  return $randomString;
}
?>
