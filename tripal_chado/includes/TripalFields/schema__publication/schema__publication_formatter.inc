<?php

class schema__publication_formatter extends ChadoFieldFormatter {
  // The default lable for this field.
  public static $default_label = 'Publication';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('schema__publication');

  /**
   *
   * @see TripalFieldFormatter::view()
   */
  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {
    $list_items = array();
    $chado_table = $this->instance['settings']['chado_table'];

    foreach ($items as $delta => $item) {

      $title = isset($item['value']['TPUB:0000039']) ? $item['value']['TPUB:0000039'] : '';
      $citation = isset($item['value']['TPUB:0000003']) ? $item['value']['TPUB:0000003'] : '';
      $entity = (is_array($item['value']) && array_key_exists('entity', $item['value'])) ? $item['value']['entity'] : '';
      if ($entity) {
        list($entity_type, $entity_id) = explode(':', $entity);
        $new_title = l($title, 'bio_data/' . $entity_id);
        // Escape anything that isn't alphanumeric
        $title = preg_replace('/([^\w])/', '\\\\$1', $title);
        $citation = preg_replace("/$title/", $new_title, $citation);
      }
      $list_items[] = $citation;
    }

    $list = '';
    krsort($list_items, SORT_NUMERIC);
    if (count($list_items) == 0) {
      $list = 'There are no publications associated with this record.';
    }
    if (count($list_items) == 1) {
      $list = $list_items[0];
    }
    if (count($list_items) > 1) {
      $list = array(
        'title' => '',
        'items' => $list_items,
        'type' => 'ol',
        'attributes' => array(),
      );
      $list = theme_item_list($list);
    }

    $element[0] = array(
      '#type' => 'markup',
      '#markup' => $list,
    );
  }
}
