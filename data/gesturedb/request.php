<?php
require_once("includes/conf.php");

header('Content-type: text/xml');
header("Cache-Control: no-cache, must-revalidate");

echo '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>';
if(isset($_REQUEST["cmd"]))
{
  switch($_REQUEST["cmd"])
  {
    case 'getStrings':
      getStrings();
      break;
    case 'getData':
      getData();
      break;
    case 'logonUser':
      logonUser();
      break;
    case 'registerUser':
      registerUser();
      break;
    case 'addUserPhoto':
      addUserPhoto();
      break;
    case 'getUser':
      getUser();
      break;
    case 'beginSession':
      beginSession();
      break;
    case 'getSession':
      getSession();
      break;
    case 'setSessionLanguage':
      setSessionLanguage();
      break;
    case 'setSessionUser':
      setSessionUser();
      break;
    case 'endSession':
      endSession();
      break;
    case 'getSessionGestures':
      getSessionGestures();
      break;
    case 'addSessionGesture':
      addSessionGesture();
      break;
    case 'removeSessionGesture':
      removeSessionGesture();
      break;
    case 'commitSessionGestures':
      commitSessionGestures();
      break;
    case 'addSessionMessage':
      addSessionMessage();
      break;
    case 'removeSessionMessage':
      removeSessionMessage();
      break;
    case 'sendSessionMessages':
      sendSessionMessages();
      break;
    case 'getUserGesturesAcc':
      getUserGesturesAcc();
      break;
    case 'getAllGesturesAcc':
      getAllGesturesAcc();
      break;
    case 'setVisualizationState':
      setVisualizationState();
      break;
    case 'getVisualizationState':
      getVisualizationState();
      break;
    default:
      echoError(14, $_REQUEST["cmd"]);
      break;
  }
}
else
{
  echoError(15);
}

###################################################################################################

function getStrings()
{
  global $db;

  $languageid = isset($_REQUEST["languageid"]) ? trim($_REQUEST["languageid"]) : 'fr';

// <!-- getStrings(languageid="'.$languageid.'")-->

// TODO
  echo '
<uilanguagestrings>';
  echo '
</uilanguagestrings>';
}


###################################################################################################

function getData()
{
  global $db;

  $languageid = isset($_REQUEST["languageid"]) ? trim($_REQUEST["languageid"]) : '';

// <!-- getData(languageid="'.$languageid.'")-->

  echo '
<data>';
  echo '
  <languages>';
  $languages = pg_query($db, "SELECT * FROM language ORDER BY id");
  while (is_object($language = pg_fetch_object($languages)))
  {
    if ($languageid == '' || $languageid == $language->id)
    {
      echo '
    <language>
      <id>'.$language->id.'</id>
      <name><![CDATA['.$language->name.']]></name>
    </language>';
    }
  }
  echo '
  </languages>';
  echo '
  <themes>';
  $themes = pg_query($db, "SELECT * FROM theme ORDER BY id");
  while (is_object($theme = pg_fetch_object($themes)))
  {
    echo '
    <theme>
      <id>'.$theme->id.'</id>';
    $themenames = pg_query($db, "SELECT * FROM themename WHERE id = ".$theme->id." ORDER BY languageid");
    while (is_object($themename = pg_fetch_object($themenames)))
    {
      if ($languageid == '' || $languageid == $themename->languageid)
      {
        echo '
      <name languageid="'.$themename->languageid.'"><![CDATA['.$themename->name.']]></name>';
      }
    }
    echo '
      <firstcolor>
        <red>'.$theme->fcr.'</red>
        <green>'.$theme->fcg.'</green>
        <blue>'.$theme->fcb.'</blue>
      </firstcolor>
      <secondcolor>
        <red>'.$theme->scr.'</red>
        <green>'.$theme->scg.'</green>
        <blue>'.$theme->scb.'</blue>
      </secondcolor>';
    echo '
      <gestures>';
    $gestures = pg_query($db, "SELECT * FROM gesture WHERE themeid = ".$theme->id." ORDER BY id");
    while (is_object($gesture = pg_fetch_object($gestures)))
    {
      $qrcodefile = QRCODE_PATH.$gesture->id.".png";
      if (!is_file($qrcodefile))
      {
        shell_exec("qrencode -o \"".$qrcodefile."\" -s 25 ".$gesture->id);
      }
      echo '
        <gesture>
          <id>'.$gesture->id.'</id>
          <qrcodepath><![CDATA['.substr($qrcodefile, strlen(ROOT_PATH)).']]></qrcodepath>
          <qrcodeurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].substr($qrcodefile, strlen(ROOT_PATH)).']]></qrcodeurl>
          <iconpath><![CDATA['.$gesture->iconpath.']]></iconpath>
          <iconurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->iconpath.']]></iconurl>
          <iconsmallpath><![CDATA['.$gesture->iconsmallpath.']]></iconsmallpath>
          <iconsmallurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->iconsmallpath.']]></iconsmallurl>
          <iconxsmallpath><![CDATA['.$gesture->iconxsmallpath.']]></iconxsmallpath>
          <iconxsmallurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->iconxsmallpath.']]></iconxsmallurl>
          <iconxxsmallpath><![CDATA['.$gesture->iconxxsmallpath.']]></iconxxsmallpath>
          <iconxxsmallurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->iconxxsmallpath.']]></iconxxsmallurl>';
      if ($gesture->imagepath != '')
      {
        echo '
          <imagepath><![CDATA['.$gesture->imagepath.']]></imagepath>
          <imageurl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->imagepath.']]></imageurl>';
      }
      if ($gesture->providerlogopath != '')
      {
        echo '
          <providerlogopath><![CDATA['.$gesture->providerlogopath.']]></providerlogopath>
          <providerlogourl><![CDATA[http://'.$_SERVER['HTTP_HOST'].$gesture->providerlogopath.']]></providerlogourl>';
      }
      echo '
          <co2impact>'.$gesture->co2impact.'</co2impact>
          <achievedpercent>'.number_format($gesture->achievedpercent, 2, '.', '').'</achievedpercent>
          <treeimpact>'.$gesture->treeimpact.'</treeimpact>
          <energyimpact>'.$gesture->energyimpact.'</energyimpact>
          <environmentrating>'.$gesture->environmentrating.'</environmentrating>
          <costs>'.$gesture->costs.'</costs>
          <financialsavings>'.$gesture->financialsavings.'</financialsavings>
          <savings10years>'.$gesture->savings10years.'</savings10years>
          <roitime>'.$gesture->roitime.'</roitime>
          <financialrating>'.$gesture->financialrating.'</financialrating>
          <personaladvantage><![CDATA['.$gesture->personaladvantage.']]></personaladvantage>
          <communityadvantage><![CDATA['.$gesture->communityadvantage.']]></communityadvantage>
          <advantagerating>'.$gesture->advantagerating.'</advantagerating>
          <co2impactbyswiss>'.($gesture->co2impact * $gesture->swissmultiplicationfactor).'</co2impactbyswiss>
          <energyimpactbyswiss>'.($gesture->energyimpact * $gesture->swissmultiplicationfactor).'</energyimpactbyswiss>';
      $gesturecontents = pg_query($db,
        "SELECT id, languageid, contenttype, txt, -1 as sequence, 'url' as mediatype, '' as path, '' as previewpath from gesturetext t
           WHERE t.id = ".$gesture->id.($languageid == '' ? "" : " AND t.languageid = '".$languageid."'")."
         UNION 
         SELECT id, languageid, contenttype, '' as txt, sequence, mediatype, path, previewpath from gesturecontent c
           WHERE c.id = ".$gesture->id.($languageid == '' ? "" : " AND c.languageid = '".$languageid."'")."
         ORDER BY languageid, contenttype, sequence");
      $usedlang = '';
      $usedcontenttype = '';
      while (is_object($gesturecontent = pg_fetch_object($gesturecontents)))
      {
        if ($usedlang != $gesturecontent->languageid)
        {
          if ($usedcontenttype != '')
          {
            echo '
            </'.$usedcontenttype.'>';
          }
          if ($usedlang != '')
          {
            echo '
          </gesturecontent>';
          }
          echo '
          <gesturecontent languageid="'.$gesturecontent->languageid.'">';
          $usedlang = $gesturecontent->languageid;
          $usedcontenttype = '';
        }
        if ($usedcontenttype != $gesturecontent->contenttype)
        {
          if ($usedcontenttype != '')
          {
            echo '
            </'.$usedcontenttype.'>';
          }
          echo '
            <'.$gesturecontent->contenttype.'>';
          $usedcontenttype = $gesturecontent->contenttype;
        }
        if ($gesturecontent->sequence == -1)
        {
          echo '
              <text><![CDATA['.str_replace("<strong>", "<b>",
                                 str_replace("</strong>", "</b>",
                                 str_replace("</p>", "</p>\n",
                                 str_replace("<br />", "<br />\n",
                                 html_entity_decode($gesturecontent->txt, ENT_COMPAT, 'UTF-8'))))).']]></text>';
        }
        else
        {
          echo '
              <content>
                <sequence>'.$gesturecontent->sequence.'</sequence>
                <mediatype>'.$gesturecontent->mediatype.'</mediatype>
                <path><![CDATA['.$gesturecontent->path.']]></path>
                <previewpath><![CDATA['.$gesturecontent->previewpath.']]></previewpath>
              </content>';
        }
      }
      if ($usedcontenttype != '')
      {
        echo '
            </'.$usedcontenttype.'>';
      }
      if ($usedlang != '')
      {
        echo '
          </gesturecontent>';
      }
      echo '
        </gesture>';
    }
    echo '
      </gestures>';
    echo '
    </theme>';
  }
  echo '
  </themes>';
  echo '
</data>';
}


###################################################################################################

function logonUser()
{
  global $db;

  $username = isset($_REQUEST["username"]) ? trim($_REQUEST["username"]) : '';
  $password = isset($_REQUEST["password"]) ? trim($_REQUEST["password"]) : '';

// <!-- logonUser(username="'.$username.'", password="'.$password.'")-->';

  if ($username == '' || $password == '')
  {
    echoError(1);
  }
  else
  {
    $userid = pg_fetch_result(pg_query($db, "SELECT id FROM \"user\"
                                               WHERE username = '".pg_escape_string($username)."' AND
                                                     password = '".pg_escape_string($password)."' AND
                                                     isdemo = FALSE LIMIT 1"),0,'id');
    if ($userid > 0)
    {
      echoUser($userid);
    }
    else
    {
      echoError(9, $userid);
    }
  }
}


###################################################################################################

function registerUser()
{
  global $db;

  $username = isset($_REQUEST["username"]) ? trim($_REQUEST["username"]) : '';
  $password = isset($_REQUEST["password"]) ? trim($_REQUEST["password"]) : '';
  $isemail = isset($_REQUEST["isemail"]) ? (bool)$_REQUEST["isemail"] : false;
  $languageid = isset($_REQUEST["languageid"]) ? trim($_REQUEST["languageid"]) : 'fr';
  $firstname = isset($_REQUEST["firstname"]) ? trim($_REQUEST["firstname"]) : '';
  $surname = isset($_REQUEST["surname"]) ? trim($_REQUEST["surname"]) : '';
  $address = isset($_REQUEST["address"]) ? trim($_REQUEST["address"]) : '';
  $zipcode = isset($_REQUEST["zipcode"]) ? trim($_REQUEST["zipcode"]) : '';
  $city = isset($_REQUEST["city"]) ? trim($_REQUEST["city"]) : '';
  $country = isset($_REQUEST["country"]) ? trim($_REQUEST["country"]) : '';
  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;

// <!-- registerUser(username="'.$username.'", password="'.$password.'", isemail="'.$isemail.'", languageid="'.$languageid.'", firstname="'.$firstname.'", surname="'.$surname.'", address="'.$address.'", zipcode="'.$zipcode.'", city="'.$city.'", country="'.$country.'")-->';

  if ($username == '')
  {
    echoError(1);
  }
  else
  {
    $existingusers = pg_query($db, "SELECT username FROM \"user\" WHERE username = '".pg_escape_string($username)."' LIMIT 1");
    if (pg_num_rows($existingusers) > 0)
    {
      echoError(6, $username);
    }
    else
    {
      if ($password == '')
      {
        $password = generateRandomString(8);
      }
      pg_query($db,"BEGIN");
      pg_query($db,"INSERT INTO \"user\" (username, password, isemail, languageid, firstname, surname, address, zipcode, city, country)
                VALUES ('".pg_escape_string($username)."',
                        '".pg_escape_string($password)."',
                        ".($isemail == '' ? 'false':'true').",
                        '".pg_escape_string($languageid)."',
                        '".pg_escape_string($firstname)."',
                        '".pg_escape_string($surname)."',
                        '".pg_escape_string($address)."',
                        '".pg_escape_string($zipcode)."',
                        '".pg_escape_string($city)."',
                        '".pg_escape_string($country)."')");
      $userid = pg_fetch_result(pg_query($db,"SELECT MAX(id) AS id FROM \"user\""),0,'id');
      pg_query($db,"COMMIT");
      if ($userid == null || $userid == 0)
      {
        echoError(7);
      }
      else
      {
        if ($sessionid > 0)
        {
          setSessionUserDB($sessionid, $userid);
        }
        addUserPhotoDB($userid);
        if (sendRegistrationMail($userid))
        {
          echoUser($userid);
        }
      }
    }
  }
}


###################################################################################################

function addUserPhotoDB($userid)
{
  global $db;

  $fp = fopen(LOG_PATH, 'a');
  fwrite($fp, "_SERVER: ".print_r($_SERVER, TRUE));
  fwrite($fp, "_POST: ".print_r($_POST, TRUE));
  fwrite($fp, "_FILES: ".print_r($_FILES, TRUE));
  fclose($fp);

  if (isset($_FILES["photo"]))
  {
    $uploadfile = USERPICTURE_PATH.$_SERVER["REQUEST_TIME"]."_".$_FILES["photo"]["name"];
    if (!move_uploaded_file($_FILES["photo"]["tmp_name"], $uploadfile))
    {
      echoError(17, $uploadfile);
      return FALSE;
    }
    pg_query($db, "UPDATE \"user\" SET
                          imagepath = '".pg_escape_string(substr($uploadfile,strlen(ROOT_PATH)))."'
                    WHERE id = ".$userid);
  }
  else if (isset($_POST["photo"]))
  {
    $uploadfile = USERPICTURE_PATH.$_SERVER["REQUEST_TIME"]."_".$_POST["name"];
    if (!file_put_contents($uploadfile, base64_decode($_POST["photo"])))
    {
      echoError(17, $uploadfile);
      return FALSE;
    }
    pg_query($db, "UPDATE \"user\" SET
                          imagepath = '".pg_escape_string(substr($uploadfile,strlen(ROOT_PATH)))."'
                    WHERE id = ".$userid);
  }
  return TRUE;
}

function addUserPhoto()
{
  global $db;

  $userid = isset($_REQUEST["userid"]) ? (int)$_REQUEST["userid"] : 0;

// <!-- addUserPhoto(userid="'.$userid.'")-->';

  if ($userid == 0)
  {
    echoError(2);
  }
  else if (!isset($_FILES["photo"]) && !isset($_POST["photo"]))
  {
    echoError(16);
  }
  else {
    if (addUserPhotoDB($userid))
    {
      echoUser($userid);
    }
  }
}


###################################################################################################

function getUser()
{
  global $db;

  $userid = isset($_REQUEST["userid"]) ? (int)$_REQUEST["userid"] : 0;

// <!-- getUser(userid="'.$userid.'")-->';

  if ($userid == 0)
  {
    echoError(2);
  }
  else
  {
    echoUser($userid);
  }
}


###################################################################################################

function beginSession()
{
  global $db;

  $tabletid = isset($_REQUEST["tabletid"]) ? trim($_REQUEST["tabletid"]) : '';
  $userid = isset($_REQUEST["userid"]) ? (int)$_REQUEST["userid"] : 0;
  $languageid = isset($_REQUEST["languageid"]) ? trim($_REQUEST["languageid"]) : '';

//  echo '
//<!-- beginSession(tabletid="'.$tabletid.'", userid="'.$userid.'", languageid="'.$languageid.'")-->';

  if ($tabletid == '')
  {
    echoError(3);
  }
  else
  {
    if ($languageid == '' && $userid > 0)
    {
      $languageid = trim(pg_fetch_result(pg_query($db, "SELECT languageid FROM \"user\" WHERE id = ".$userid), 0, 'languageid'));
    }
    if ($languageid == '')
    {
      $languageid = 'fr';
    }
    $existingtablet = pg_query($db, "SELECT * FROM tablet WHERE id = '".pg_escape_string($tabletid)."' LIMIT 1");
    if (pg_num_rows($existingtablet) == 0)
    {
      pg_query($db, "INSERT INTO tablet (id) VALUES ('".pg_escape_string($tabletid)."')");
    }
    $sessionfound = false;
    if ($userid > 0)
    {
      $existingsession = pg_query($db, "SELECT * FROM usersession WHERE userid = ".$userid." ORDER BY id DESC LIMIT 1");
      if (pg_num_rows($existingsession) > 0)
      {
        $session = pg_fetch_object($existingsession);
        pg_query($db, "UPDATE usersession
                          SET tabletid = '".pg_escape_string($tabletid)."',
                              startedat = now(),
                              languageid = '".$languageid."'
                        WHERE id = ".$session->id);
        echoSession($session->id);
        $sessionfound = true;
      }
    }
    if ($sessionfound == false)
    {
      pg_query($db,"BEGIN");
      if ($userid > 0)
      {
        pg_query($db,"INSERT INTO usersession (tabletid, userid, languageid)
                        VALUES ('".pg_escape_string($tabletid)."', ".$userid.", '".$languageid."')");
      }
      else
      {
        pg_query($db,"INSERT INTO usersession (tabletid, languageid)
                        VALUES ('".pg_escape_string($tabletid)."', '".$languageid."')");
      }
      $sessionid = pg_fetch_result(pg_query($db,"SELECT MAX(id) AS id FROM usersession"),0,'id');
      pg_query($db, "COMMIT");
      if ($sessionid == null || $sessionid == 0)
      {
        echoError(10);
      }
      else
      {
        echoSession($sessionid);
      }
    }
  }
}


###################################################################################################

function getSession()
{
  global $db;

  $tabletid = isset($_REQUEST["tabletid"]) ? trim($_REQUEST["tabletid"]) : '';

// <!-- getSession(tabletid="'.$tabletid.'")-->';

  if ($tabletid == '')
  {
    echoError(3);
  }
  else
  {
    $sessionid = pg_fetch_result(pg_query($db, "SELECT id FROM usersession
                                                 WHERE tabletid = '".pg_escape_string($tabletid)."'
                                                 ORDER BY startedat DESC LIMIT 1"), 0, 'id');
    if ($sessionid == null || $sessionid == 0)
    {
      echoError(12, $tabletid);
    }
    else
    {
      echoSession($sessionid);
    }
  }
}


###################################################################################################

function setSessionLanguage()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;
  $languageid = isset($_REQUEST["languageid"]) ? trim($_REQUEST["languageid"]) : '';

// <!-- setSessionLanguage(sessionid="'.$sessionid.'", languageid="'.$languageid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else if ($languageid == '')
  {
    echoError(18);
  }
  else {
    pg_query($db, "UPDATE usersession SET languageid = '".$languageid."' WHERE id = ".$sessionid);
    echoSession($sessionid);
  }
}

###################################################################################################

function setSessionUserDB($sessionid, $userid)
{
  global $db;

  pg_query($db, "BEGIN");
  pg_query($db, "UPDATE sessiongestures
                    SET sessionid = ".$sessionid."
                  WHERE sessionid <> ".$sessionid." AND
                        sessionid IN (SELECT id FROM usersession
                                       WHERE userid = ".$userid.") AND
                        gestureid NOT IN (SELECT gestureid FROM sessiongestures
                                           WHERE sessionid = ".$sessionid.")");
  pg_query($db, "DELETE FROM sessiongestures
                  WHERE sessionid <> ".$sessionid." AND
                        sessionid IN (SELECT id FROM usersession 
                                       WHERE userid = ".$userid.")");
  pg_query($db, "UPDATE sessionmessages
                    SET sessionid = ".$sessionid."
                  WHERE sessionid <> ".$sessionid." AND
                        sessionid IN (SELECT id FROM usersession
                                       WHERE userid = ".$userid.") AND
                        gestureid NOT IN (SELECT gestureid FROM sessionmessages
                                           WHERE sessionid = ".$sessionid.")");
  pg_query($db, "DELETE FROM sessionmessages
                  WHERE sessionid <> ".$sessionid." AND
                        sessionid IN (SELECT id FROM usersession 
                                       WHERE userid = ".$userid.")");
  pg_query($db, "UPDATE usersession
                    SET userid = ".$userid."
                  WHERE id = ".$sessionid);
  pg_query($db, "UPDATE usersession
                    SET userid = NULL
                  WHERE id <> ".$sessionid." AND userid = ".$userid);
  pg_query($db, "COMMIT");
}

function setSessionUser()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;
  $userid = isset($_REQUEST["userid"]) ? (int)$_REQUEST["userid"] : 0;

// <!-- setSessionUser(sessionid="'.$sessionid.'", userid="'.$userid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else if ($userid == 0)
  {
    echoError(2);
  }
  else {
    setSessionUserDB($sessionid, $userid);
    echoSession($sessionid);
  }
}


###################################################################################################

function endSession()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;

// <!-- endSession(sessionid="'.$sessionid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else
  {
    pg_query($db, "UPDATE usersession SET finishedat = now() WHERE id = ".$sessionid);
    
    $userid = pg_fetch_result(pg_query($db, "SELECT userid FROM usersession
                                              WHERE id = ".$sessionid), 0, 'userid');
    if ($userid > 0)
    {
      if (setVisualizationActiveDB($userid) == 0)
      {
        echoError(20);
        return;
      }
      $message = sprintf("%d", $userid);
      if ($socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP))
      {
        socket_sendto($socket, $message, strlen($message), 0, VISUALIZATION_IP, VISUALIZATION_PORT);
      }
    }

    echoSession($sessionid);
  }
}


###################################################################################################

function getSessionGestures()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;

// <!-- getSessionGestures(sessionid="'.$sessionid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else
  {
    echoSession($sessionid);
  }
}


###################################################################################################

function addSessionGesture()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;
  $gestureid = isset($_REQUEST["gestureid"]) ? (int)$_REQUEST["gestureid"] : 0;

// <!-- addSessionGesture(sessionid="'.$sessionid.'", gestureid="'.$gestureid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else if ($gestureid == 0)
  {
    echoError(5);
  }
  else
  {
    $maxsequence = pg_fetch_result(pg_query($db, "SELECT MAX(sequence) AS sequence FROM sessiongestures
                                                   WHERE sessionid = ".$sessionid), 0, 'sequence');
    if ($maxsequence == null)
    {
      $maxsequence = 0;
    }
    if (!pg_query($db, "INSERT INTO sessiongestures (sessionid, gestureid, sequence)
                          VALUES (".$sessionid.", ".$gestureid.", ".($maxsequence + 1).")"))
    {
      echoError(13);
    }
    else
    {
      echoSession($sessionid);
    }
  }
}


###################################################################################################

function removeSessionGesture()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;
  $gestureid = isset($_REQUEST["gestureid"]) ? (int)$_REQUEST["gestureid"] : 0;

// <!-- removeSessionGesture(sessionid="'.$sessionid.'", gestureid="'.$gestureid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else if ($gestureid == 0)
  {
    echoError(5);
  }
  else
  {
    pg_query($db, "DELETE FROM sessiongestures WHERE sessionid = ".$sessionid." AND gestureid = ".$gestureid);
    echoSession($sessionid);
  }
}


###################################################################################################

function commitSessionGestures()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;

// <!-- commitSessionGestures(sessionid="'.$sessionid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else
  {
    pg_query($db, "UPDATE usersession SET committedat = now() WHERE id = ".$sessionid);
    pg_query($db, "UPDATE sessiongestures SET committed = true WHERE sessionid = ".$sessionid);
    echoSession($sessionid);
  }
}


###################################################################################################

function addSessionMessage()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;
  $gestureid = isset($_REQUEST["gestureid"]) ? (int)$_REQUEST["gestureid"] : 0;

// <!-- addSessionMessage(sessionid="'.$sessionid.'", gestureid="'.$gestureid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else if ($gestureid == 0)
  {
    echoError(5);
  }
  else
  {
    $maxsequence = pg_fetch_result(pg_query($db, "SELECT MAX(sequence) AS sequence FROM sessionmessages
                                                   WHERE sessionid = ".$sessionid), 0, 'sequence');
    if ($maxsequence == null)
    {
      $maxsequence = 0;
    }
    if (!pg_query($db, "INSERT INTO sessionmessages (sessionid, gestureid, sequence)
                          VALUES (".$sessionid.", ".$gestureid.", ".($maxsequence + 1).")"))
    {
      echoError(13);
    }
    else
    {
      echoSession($sessionid);
    }
  }
}


###################################################################################################

function removeSessionMessage()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;
  $gestureid = isset($_REQUEST["gestureid"]) ? (int)$_REQUEST["gestureid"] : 0;

// <!-- removeSessionMessage(sessionid="'.$sessionid.'", gestureid="'.$gestureid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else if ($gestureid == 0)
  {
    echoError(5);
  }
  else
  {
    pg_query($db, "DELETE FROM sessionmessages WHERE sessionid = ".$sessionid." AND gestureid = ".$gestureid);
    echoSession($sessionid);
  }
}


###################################################################################################

function sendSessionMessages()
{
  global $db;

  $sessionid = isset($_REQUEST["sessionid"]) ? (int)$_REQUEST["sessionid"] : 0;

// <!-- sendSessionMessages(sessionid="'.$sessionid.'")-->';

  if ($sessionid == 0)
  {
    echoError(4);
  }
  else
  {
// TODO: actually send the email
    pg_query($db, "UPDATE usersession SET sentat = now() WHERE id = ".$sessionid);
    pg_query($db, "UPDATE sessionmessages SET sent = true WHERE sessionid = ".$sessionid);

    echoSession($sessionid);
  }
}


###################################################################################################

function getUserGesturesAcc()
{
  global $db;

  $userid = isset($_REQUEST["userid"]) ? (int)$_REQUEST["userid"] : 0;

// <!-- getUserGesturesAcc(userid="'.$userid.'")-->';

  $exhibitionstate = getExhibitionState();

  if ($userid == 0)
  {
    echoError(2);
  }
  else
  {
    echo '
<result>';
    echoUser($userid);
    echo '
  <overall>';
    $overallco2impact = 0;
    $themegesturesuser = pg_query($db, "SELECT SUM(co2impact) AS co2impact,
                                               SUM(achievedpercent) AS achievedpercent,
                                               SUM(treeimpact) AS treeimpact,
                                               SUM(energyimpact) AS energyimpact,
                                               SUM(costs) AS costs,
                                               SUM(savings10years) AS savings10years,
                                               SUM(co2impactbyswiss) AS co2impactbyswiss,
                                               SUM(energyimpactbyswiss) AS energyimpactbyswiss
                                          FROM themegesturesuser WHERE userid = ".$userid);
    while (is_object($theme = pg_fetch_object($themegesturesuser)))
    {
      echo '
      <co2impact>'.number_format($theme->co2impact, 3, '.', '').'</co2impact>
      <achievedpercent>'.number_format($theme->achievedpercent, 2, '.', '').'</achievedpercent>
      <treeimpact>'.number_format($theme->treeimpact, 0, '.', '').'</treeimpact>
      <energyimpact>'.number_format($theme->energyimpact, 0, '.', '').'</energyimpact>
      <costs>'.number_format($theme->costs, 0, '.', '').'</costs>
      <savings10years>'.number_format($theme->savings10years, 0, '.', '').'</savings10years>
      <co2impactbyswiss>'.number_format($theme->co2impactbyswiss, 0, '.', '').'</co2impactbyswiss>
      <energyimpactbyswiss>'.number_format($theme->energyimpactbyswiss, 0, '.', '').'</energyimpactbyswiss>';
      if (is_object($exhibitionstate))
      {
        echo '
      <co2comparison>'.number_format($theme->co2impact / $exhibitionstate->co2comparison, 2, '.', '').'</co2comparison>
      <energycomparison>'.number_format($theme->energyimpact / $exhibitionstate->energycomparison, 2, '.', '').'</energycomparison>
      <co2comparisonbyswiss>'.number_format($theme->co2impactbyswiss / $exhibitionstate->co2comparison, 2, '.', '').'</co2comparisonbyswiss>
      <energycomparisonbyswiss>'.number_format($theme->energyimpactbyswiss / $exhibitionstate->energycomparison, 2, '.', '').'</energycomparisonbyswiss>';
      }
      $overallco2impact = $theme->co2impact;
    }
    echo '
  </overall>
  <themes>';
    $themegesturesuser = pg_query($db, "SELECT t.id, tgu.* FROM theme t
                                          LEFT JOIN themegesturesuser tgu ON t.id = tgu.themeid AND
                                                                             tgu.userid = ".$userid."
                                         ORDER BY t.id");
    while (is_object($theme = pg_fetch_object($themegesturesuser)))
    {
      echo '
    <theme>
      <id>'.$theme->id.'</id>
      <co2impact>'.number_format($theme->co2impact, 3, '.', '').'</co2impact>
      <achievedpercent>'.number_format($theme->achievedpercent, 2, '.', '').'</achievedpercent>
      <overallpercent>'.number_format($theme->co2impact * 100 / $overallco2impact, 2, '.', '').'</overallpercent>
      <treeimpact>'.number_format($theme->treeimpact, 0, '.', '').'</treeimpact>
      <energyimpact>'.number_format($theme->energyimpact, 0, '.', '').'</energyimpact>
      <costs>'.number_format($theme->costs, 0, '.', '').'</costs>
      <savings10years>'.number_format($theme->savings10years, 0, '.', '').'</savings10years>
      <co2impactbyswiss>'.number_format($theme->co2impactbyswiss, 0, '.', '').'</co2impactbyswiss>
      <energyimpactbyswiss>'.number_format($theme->energyimpactbyswiss, 0, '.', '').'</energyimpactbyswiss>
    </theme>';
    }
    echo '
  </themes>
</result>';
  }
}


###################################################################################################

function getAllGesturesAcc()
{
  global $db;

// <!-- getAllGesturesAcc()-->';

  $exhibitionstate = getExhibitionState();

  echo '
<result>';
  $nrusers = pg_fetch_result(pg_query($db, "SELECT COUNT(*) as nr FROM \"user\"
                                               WHERE id IN (SELECT userid FROM usersession) AND
                                                     isdemo = FALSE"),0,'nr');
  echo '
  <nrusers>'.$nrusers.'</nrusers>';
  echo '
  <overall>';
    $themegesturesall = pg_query($db, "SELECT SUM(tga.co2impact) AS co2impact,
                                              SUM(tga.achievedpercent) AS achievedpercent,
                                              SUM(tga.treeimpact) AS treeimpact,
                                              SUM(tga.energyimpact) AS energyimpact,
                                              SUM(tga.costs) AS costs,
                                              SUM(tga.savings10years) AS savings10years,
                                              SUM(tgb.co2impactbyswiss) AS co2impactbyswiss,
                                              SUM(tgb.energyimpactbyswiss) AS energyimpactbyswiss
                                         FROM themegesturesall tga
                                         LEFT JOIN themegesturesbyswiss tgb ON tgb.themeid = tga.themeid");
    $overallco2impact = 0;
    while (is_object($theme = pg_fetch_object($themegesturesall)))
    {
      echo '
      <co2impact>'.number_format($theme->co2impact, 3, '.', '').'</co2impact>
      <achievedpercent>'.number_format($theme->achievedpercent, 2, '.', '').'</achievedpercent>
      <treeimpact>'.number_format($theme->treeimpact, 0, '.', '').'</treeimpact>
      <energyimpact>'.number_format($theme->energyimpact, 0, '.', '').'</energyimpact>
      <costs>'.number_format($theme->costs, 0, '.', '').'</costs>
      <savings10years>'.number_format($theme->savings10years, 0, '.', '').'</savings10years>
      <co2impactbyswiss>'.number_format($theme->co2impactbyswiss, 0, '.', '').'</co2impactbyswiss>
      <energyimpactbyswiss>'.number_format($theme->energyimpactbyswiss, 0, '.', '').'</energyimpactbyswiss>';
      if (is_object($exhibitionstate))
      {
        echo '
      <co2comparison>'.number_format($theme->co2impact / $exhibitionstate->co2comparison, 2, '.', '').'</co2comparison>
      <energycomparison>'.number_format($theme->energyimpact / $exhibitionstate->energycomparison, 2, '.', '').'</energycomparison>
      <co2comparisonbyswiss>'.number_format($theme->co2impactbyswiss / $exhibitionstate->co2comparison, 2, '.', '').'</co2comparisonbyswiss>
      <energycomparisonbyswiss>'.number_format($theme->energyimpactbyswiss / $exhibitionstate->energycomparison, 2, '.', '').'</energycomparisonbyswiss>';
      }
      $overallco2impact = $theme->co2impact;
    }
    echo '
  </overall>
  <themes>';
  $themegesturesall = pg_query($db, "SELECT t.id, tga.*, tgb.co2impactbyswiss, tgb.energyimpactbyswiss,
                                            t.fcr, t.fcg, t.fcb, t.scr, t.scg, t.scb,
                                            tn1.name as name1, tn2.name as name2
                                       FROM theme t
                                       LEFT JOIN themegesturesall tga ON tga.themeid = t.id
                                       LEFT JOIN themegesturesbyswiss tgb ON tgb.themeid = t.id
                                       LEFT JOIN themename tn1 ON tn1.id = t.id AND tn1.languageid = 'de'
                                       LEFT JOIN themename tn2 ON tn2.id = t.id AND tn2.languageid = 'fr'
                                      ORDER BY t.id");
  while (is_object($theme = pg_fetch_object($themegesturesall)))
  {
    echo '
    <theme>
      <id>'.$theme->id.'</id>
      <name languageid="de">'.$theme->name1.'</name>
      <name languageid="fr">'.$theme->name2.'</name>
      <firstcolor>
        <red>'.$theme->fcr.'</red>
        <green>'.$theme->fcg.'</green>
        <blue>'.$theme->fcb.'</blue>
      </firstcolor>
      <secondcolor>
        <red>'.$theme->scr.'</red>
        <green>'.$theme->scg.'</green>
        <blue>'.$theme->scb.'</blue>
      </secondcolor>
      <co2impact>'.number_format($theme->co2impact, 3, '.', '').'</co2impact>
      <achievedpercent>'.number_format($theme->achievedpercent, 2, '.', '').'</achievedpercent>
      <overallpercent>'.number_format($theme->co2impact * 100 / $overallco2impact, 2, '.', '').'</overallpercent>
      <treeimpact>'.number_format($theme->treeimpact, 0, '.', '').'</treeimpact>
      <energyimpact>'.number_format($theme->energyimpact, 0, '.', '').'</energyimpact>
      <costs>'.number_format($theme->costs, 0, '.', '').'</costs>
      <savings10years>'.number_format($theme->savings10years, 0, '.', '').'</savings10years>
      <co2impactbyswiss>'.number_format($theme->co2impactbyswiss, 0, '.', '').'</co2impactbyswiss>
      <energyimpactbyswiss>'.number_format($theme->energyimpactbyswiss, 0, '.', '').'</energyimpactbyswiss>
    </theme>';
  }
  echo '
  </themes>
</result>';
}


###################################################################################################

function setVisualizationActiveDB($userid)
{
  global $db;

  $dbresult = pg_query($db, "UPDATE exhibitionstate
                                SET visualizationuserid = ".$userid."
                              WHERE visualizationuserid IS NULL");
  return pg_affected_rows($dbresult);
}

function setVisualizationState()
{
  global $db;

  $on = isset($_REQUEST["on"]) ? (bool)$_REQUEST["on"] : false;
  $userid = isset($_REQUEST["userid"]) ? (int)$_REQUEST["userid"] : 0;

// <!-- setVisualizationState(on='.$on.', userid='.$userid.')-->';

  if ($on)
  {
    if ($userid == 0)
    {
      echoError(2);
      return;
    }
    if (setVisualizationActiveDB($userid) == 0)
    {
      echoError(20);
      return;
    }
  }
  else
  {
    pg_query($db, "UPDATE exhibitionstate SET visualizationuserid = NULL");
  }

  $exhibitionstate = getExhibitionState();
  if (is_object($exhibitionstate))
  {
    echo '
<visualizationstate>';
    if ($exhibitionstate->visualizationuserid > 0)
    {
      echo '
  <on>1</on>
  <userid>'.$exhibitionstate->visualizationuserid.'</userid>
</visualizationstate>';
    }
    else
    {
      echo '
  <on>0</on>
</visualizationstate>';
    }
  }
}



###################################################################################################

function getVisualizationState()
{
// <!-- getVisualizationState()-->';

  $exhibitionstate = getExhibitionState();
  if (is_object($exhibitionstate))
  {
    echo '
<visualizationstate>';
    if ($exhibitionstate->visualizationuserid > 0)
    {
      echo '
  <on>1</on>
  <userid>'.$exhibitionstate->visualizationuserid.'</userid>
</visualizationstate>';
    }
    else
    {
      echo '
  <on>0</on>
</visualizationstate>';
    }
  }
}

