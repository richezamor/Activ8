<?php
// $Id: ckeditor_swf.admin.inc,v 1.1 2010/07/15 15:43:01 anrikun Exp $

/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 */

function ckeditor_swf_admin_form($form_state) {
  $form['notice'] = array(
    '#value' => '<p><strong>Notice:</strong> this administration page is a preliminary version and should be updated to a more user-friendly one in next releases.</p>',
  );
  $form['players_php'] = array(
    '#type' => 'textarea',
    '#title' => t('Players configuration PHP code'),
    '#default_value' => variable_get('ckeditor_swf_players_php', 'return array();'),
    '#description' => '',
    '#rows' => 15,
    '#required' => TRUE,
    '#wysiwyg' => FALSE,
  );
  $form['instructions'] = array(
    '#value' => '<p>Here you can configure the players that <em>CKEditor SWF</em> will use to embed FLV and MP3 files. You can ignore this page if you do not need this feature.</p>'
      .'<p>Below are 2 sample configurations. Choose the one that suits your needs, copy the associated configuration PHP code, then paste it into the above textarea, in place of its previous content. Finally, click on the <em>Save</em> button at the bottom of the page.</p>'
      .'<h3><strong>Sample configuration #1</strong></h3>'
      .'<p>It uses <a href="http://www.longtailvideo.com/players/jw-flv-player">JW Player</a> both for FLV and MP3 playback.<br />'
      .'It assumes that you unpacked the content of <em>mediaplayer.zip</em> to the <em>sites/all/libraries</em> directory.<br />'
      .'If the file <em>player.swf</em> is somewhere else on your server, adjust the path parameter accordingly.<br />'
      .'This path must be relative to the Drupal installation directory.</p>'
      ."<pre style=\"border:1px solid #CCC;padding:5px;\">return array(
  'video/x-flv' => array(
    'path' => 'sites/all/libraries/mediaplayer/player.swf',
    'offsetHeight' => 24,
    'fileName' => 'file',
  ),
  'audio/mpeg' => array(
    'path' => 'sites/all/libraries/mediaplayer/player.swf',
    'offsetHeight' => 0,
    'fileName' => 'file',
    'defaultWidth' => 280,
    'defaultHeight' => 24,
  ),
);</pre>"
      .'<h3><strong>Sample configuration #2</strong></h3>'
      .'<p>It uses JW Player for FLV playback (see #1 about this) and <a href="http://wpaudioplayer.com/download">WordPress Audio Standalone Player = 1 Pixel Out</a> for MP3 playback.<br />'
      .'It assumes that you unpacked the content of <em>audio-player-standalone.zip</em> to the <em>sites/all/libraries</em> directory.<br />'
      .'If the file <em>player.swf</em> is somewhere else on your server, adjust the path parameter accordingly.<br />'
      .'This path must be relative to the Drupal installation directory.</p>'
      ."<pre style=\"border:1px solid #CCC;padding:5px;\">return array(
  'video/x-flv' => array(
    'path' => 'sites/all/libraries/mediaplayer/player.swf',
    'offsetHeight' => 24,
    'fileName' => 'file',
  ),
  'audio/mpeg' => array(
    'path' => 'sites/all/libraries/audio-player/player.swf',
    'offsetHeight' => 0,
    'fileName' => 'soundFile',
    'defaultWidth' => 290,
    'defaultHeight' => 24,
  ),
);</pre>"
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  return $form;
}

function ckeditor_swf_admin_form_validate($form, &$form_state) {
  $elements = $form['players_php'];
  $players_php = $elements['#value'];
  if (strlen($players_php) > 0) {
    ob_start();
    $players = eval($players_php);
    ob_end_clean();
    if (!is_array($players)) {
      form_error($elements, t('!name must return an array.', array('!name' => $elements['#title'])));
    }
  }
}

function ckeditor_swf_admin_form_submit($form, &$form_state) {
  $players_php = $form_state['values']['players_php'];
  variable_set('ckeditor_swf_players_php', $players_php);
  ob_start();
  $players = eval($players_php);
  ob_end_clean();
  variable_set('ckeditor_swf_players', $players);
  drupal_set_message(t('The configuration options have been saved.'));
}
