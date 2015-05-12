
(function($) {

  Drupal.CulturefeedSearch = Drupal.CulturefeedSearch || {};

  /**
   * Init the location autocomplete.
   */
  Drupal.behaviors.culturefeedSearchUiCityActorFacet = {
    attach: function(context, settings) {

      $("#edit-block-location-search").once('location-search-init').categorisedAutocomplete({
        source: Drupal.CulturefeedSearch.getLocationData,
        select: function(event, ui) {

          // Actors are direct links.
          if (ui.item.type == 'actor') {
            window.location.href = ui.item.suggestion;
          }
          // Trigger location search.
          else {
            $(this).val(ui.item.suggestion);
            $('.location-search-submit').focus();
            this.form.submit();
          }

        },
        search: function(){
          $(this).addClass('throbbing');
        },
        open: function(event, ui) {
          $(this).removeClass('throbbing');
          // Workaround for autoFocus missing before version 1.8.11
          // (http://jqueryui.com/changelog/1.8.11/)
          // We only check from 1.8.7, the version shipped with Drupal.
          var version = $.ui.version;
          var old = ['1.8.7', '1.8.8.', '1.8.9', '1.8.10'];
          if ($.inArray(version, old) >= 0) {
            $(this).data("autocomplete").menu.next(event);
          }
        },
        autoFocus: true,
      });

      $("#edit-where").once('location-search-init').categorisedAutocomplete({
        source: Drupal.CulturefeedSearch.getLocationData,
        select: function(event, ui) {

          // Actors are direct links.
          if (ui.item.type == 'actor') {
            window.location.href = ui.item.suggestion;
          }
          // Trigger location search.
          else {
            $(this).val(ui.item.suggestion);
          }

        },
        open: function(event, ui) {
          // Workaround for autoFocus missing before version 1.8.11
          // (http://jqueryui.com/changelog/1.8.11/)
          // We only check from 1.8.7, the version shipped with Drupal.
          var version = $.ui.version;
          var old = ['1.8.7', '1.8.8.', '1.8.9', '1.8.10'];
          if ($.inArray(version, old) >= 0) {
            $(this).data("autocomplete").menu.next(event);
          }
        },
        autoFocus: true,
      });

    }
  };

  /**
   * Get the data for the location autocomplete
   */
  Drupal.CulturefeedSearch.getLocationData = function(term, callback) {
    var widget = $(this.element);
    $.ajax({
      url: Drupal.settings.basePath + Drupal.settings.pathPrefix + 'autocomplete/culturefeed_ui/city-actor-suggestion/' + term.term,
      success: function(data) {
        if (data.length === 0) {
          widget.removeClass('throbbing');
        }
        else {
          $.each(data, function(index, element) {
            if (!(element.label.match(/^\d+/))) {
              if (!(element.label.match(/^Provinc|Regio+/)) && (element.type == 'city')) {
                element.label += ' (' + Drupal.t('all municipalities') + ')';
              }
            }
          });            
        }
        callback(data);
      },
      error: function() {
        callback([]);
      }
    });
  }



})(jQuery);
